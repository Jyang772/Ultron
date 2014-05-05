#ifndef LOGIN_H
#define LOGIN_H




QNetworkAccessManager network;
QByteArray loginData("user=myName&password=myPassword");
QNetworkRequest request(QUrl("http://mySite.com/login"));
QNetworkReply* pReply(network.post(request, loginData);





#endif // LOGIN_H
