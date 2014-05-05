#include "downloader.h"

#include <string>
//#include <QWebView>
using namespace std;



Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
}

void Downloader::doDownload()
{
    manager = new QNetworkAccessManager(this);


    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    QByteArray loginData("username=user&password=pass");
    QNetworkRequest request(QUrl("http://moodle.redlands.edu/mod/resource/view.php?id=114198"));
    manager->post(request,loginData);


    QUrl URL = QUrl("http://moodle.redlands.edu/mod/resource/view.php?id=114198");
    manager->get(QNetworkRequest(URL));

/*
    QNetworkAccessManager network;
    QByteArray loginData("user=myName&password=myPassword");
    QNetworkRequest request(QUrl("http://mySite.com/login"));
    QNetworkReply* pReply(network.post(request, loginData);
*/

}

void Downloader::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {

        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();



        QFile *file = new QFile("lol");
        if(file->open(QFile::WriteOnly))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }

    reply->deleteLater();
}

