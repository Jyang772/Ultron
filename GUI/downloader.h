#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <string>
#include <QObject>
/*
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
*/


#include <mainwindow.h>




class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

    void doDownload();

    QString username;
    QString password;

signals:

public slots:



private:




};






#endif // DOWNLOADER_H
