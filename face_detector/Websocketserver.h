#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include "mainHeader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "QWsServer.h"
#include "QWsSocket.h"
#include <QImage>
#include <QBuffer>

class WebSocketServer : public QObject
{
    Q_OBJECT

    public:
        WebSocketServer(int port = 80, QtWebsocket::Protocol protocol = QtWebsocket::Tcp);

    public slots:
        void processNewConnection();
        void processMessage(QString message);
        void processPong(quint64 elapsedTime);
        void socketDisconnected();
        void sendImage(cv::Mat image);
        void sendMessage(QString message);

    private:
        QtWebsocket::QWsServer* server;
        QList<QtWebsocket::QWsSocket*> clients;
        QString toReadableAscii(QString string);
        QString encodeToBase64(QImage image);
};

#endif // WEBSOCKETSERVER_H
