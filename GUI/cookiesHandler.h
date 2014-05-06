#ifndef COOKIESHANDLER_H
#define COOKIESHANDLER_H


#include <string>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>
#include <QAuthenticator>
#include <QUrlQuery>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>

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
        QNetworkRequest r(mUrl);
        //r.setHeader(QNetworkRequest::CookieHeader, var);
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
        //End Cookies//

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


                //if redirected URL is not the same as requested, then POST again
                if(rUrl != mUrl){

                    qDebug() << rUrl;

                                   mManager->post(QNetworkRequest(rUrl),login);
                                   return;
                }


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
        delete file;
    }

private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
    QUrl rUrl;
    QByteArray login;
    QVariant var;
};


#endif // COOKIESHANDLER_H
