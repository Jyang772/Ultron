#ifndef COOKIESHANDLER_H
#define COOKIESHANDLER_H


#include "mainwindow.h"
#include <string>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QEventLoop>
#include <QList>
#include <QAuthenticator>
#include <QUrlQuery>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QTextStream>


class cookiesHandler: public QObject{
    Q_OBJECT

public:
    cookiesHandler(QObject *parent = 0) : QObject(parent){
        mManager = new QNetworkAccessManager(this);
        mManager->setCookieJar(new QNetworkCookieJar(this));
connect(mManager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
    }

    void sendPostRequest(const QUrl &url, const QByteArray &data){
        mUrl = url;
        login = data;
        QNetworkRequest r(mUrl);
        mManager->post(r, data);
    }

    void sendGetRequest(const QUrl &url)
    {
        mUrl = url;
        test = mUrl;
        QNetworkRequest r(mUrl);
        mManager->get(r);
    }




    virtual ~cookiesHandler(){}

private slots:
    void replyFinished(QNetworkReply *reply){
        if (reply->error() != QNetworkReply::NoError){
            qWarning() << "ERROR:" << reply->errorString();
            return;
        }




        //Cookies//
        QList<QNetworkCookie>  cookies = mManager->cookieJar()->cookiesForUrl(mUrl);
        qDebug() << "COOKIES for" << mUrl.host() << cookies;

        QString str;
        QDebug dStream(&str);

        dStream << mUrl.host() << cookies;

        //End Cookies//


//Output in file//
        QFile lawl("debug");
        if(remove)                  //Remove existing file
           { lawl.remove();
            remove = false;}

        lawl.open(QIODevice::Append | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&lawl);
        out << str << endl;
        out << reply->header(QNetworkRequest::ContentTypeHeader).toString() << endl;
        out << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString() << endl;
        out << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong() << endl;
        out << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;
        out << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString() << endl;





        int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                if (v >= 200 && v < 300) // Success
                {


                    getFile(reply);

                     // Here we got the final reply
                   return;
                }
                else if (v >= 300 && v < 400) // Redirection
                {
                    /* Use Cookies for Login */

                    /********************/

                qDebug() << "REDIRECTING";



                rUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

                if(rUrl != mUrl)
                 {

                    mManager->post(QNetworkRequest(rUrl),login);
                    return;}


                qDebug() << rUrl;
                qDebug() << mUrl;
                out << QString("redirected: " + rUrl.toEncoded()) << endl;

                    QNetworkRequest r(mUrl);
                    QVariant var;
                    var.setValue(cookies);

                    r.setHeader(QNetworkRequest::CookieHeader, var);
                    mManager->get(r);
                    return;

                }




    }


    void getFile(QNetworkReply *reply)
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "redirected: " << reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();




        QFile *file = new QFile("lol");
        if(file->open(QFile::WriteOnly))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
/*
        QFile lawl("LAWL");
        lawl.open(QIODevice::Append | QIODevice::Text | QIODevice::Truncate);
        QTextStream out(&lawl);
        out << reply->header(QNetworkRequest::ContentTypeHeader).toString() << endl;
        out << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString() << endl;
        out << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong() << endl;
        out << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << endl;
        out << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString() << endl;
        out << QString("redirected: " + rUrl.toEncoded());
*/


        delete file;

    }

private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
    QUrl rUrl;
    QUrl test;
    QByteArray login;
    QVariant var;
    QFile Test;




public:
    bool finished = false;
    bool remove = true;


};


#endif // COOKIESHANDLER_H
