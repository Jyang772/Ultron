#include "downloader.h"
#include "cookiesHandler.h"

#include <string>

using namespace std;



Downloader::Downloader(QObject *parent) :
    QObject(parent)
{
}

void Downloader::doDownload()
{




    QByteArray loginData;
    //loginData.append("username="+username+"&password="+password+"&action=login");
    loginData.append("username=justin_yang&password=bee1230");


    cookiesHandler* test = new cookiesHandler(this);
    QUrl url("https://moodle.redlands.edu/login/index.php");
    QUrl request("http://moodle.redlands.edu/my/");
    test->sendPostRequest(url, loginData);
    //test->sendGetRequest(request);



/*
    QNetworkAccessManager network;
    QByteArray loginData("user=myName&password=myPassword");
    QNetworkRequest request(QUrl("http://mySite.com/login"));
    QNetworkReply* pReply(network.post(request, loginData);
*/


}

/*
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
}
*/
