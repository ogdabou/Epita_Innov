#include "Websocketserver.h"
#include <QWsServer.h>
#include <QWsSocket.h>
#include <QString>

WebSocketServer::WebSocketServer(int port, QtWebsocket::Protocol protocol)
{
    server = new QtWebsocket::QWsServer(this, protocol);
    if (! server->listen(QHostAddress::Any, port))
    {
        std::cout << tr("Error: Can't launch server").toStdString() << std::endl;
        std::cout << tr("QWsServer error : %1").arg(server->errorString()).toStdString() << std::endl;
    }
    else
    {
        std::cout << tr("WebSocket server is listening on port %1").arg(port).toStdString() << std::endl;
    }
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(processNewConnection()));
}

void WebSocketServer::processNewConnection()
{
    QtWebsocket::QWsSocket* clientSocket = server->nextPendingConnection();
    QObject::connect(clientSocket, SIGNAL(frameReceived(QString)), this, SLOT(processMessage(QString)));
    QObject::connect(clientSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    QObject::connect(clientSocket, SIGNAL(pong(quint64)), this, SLOT(processPong(quint64)));
    clients << clientSocket;
    std::cout << tr("Client connected").toStdString() << std::endl;
}

void WebSocketServer::sendImage(cv::Mat image)
{
    QtWebsocket::QWsSocket* client;
    uchar* datas = image.data;
    std::cout << image.cols * image.rows << std::endl;
    std::cout << "coucou" << std::endl;
    QString dataString;
    for (int i = 0; i < (image.cols * image.rows ) - 2 ; i++)
    {
        dataString += datas[i];

    }
    qDebug() << dataString;
    std::cout << "Sending an image" << std::endl;
    cv::Mat dst;
    cv::cvtColor(image, dst, CV_BGR2RGB);
    QImage imageAsQImage((uchar*)dst.data, dst.cols, dst.rows, QImage::Format_RGB32);


    QString encodedImage = encodeToBase64(imageAsQImage);

    foreach(client, clients)
    {
        client->write(encodedImage);
        //client->write(dataString);
    }
}

QString WebSocketServer::encodeToBase64(QImage image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer,"PNG");
    return QString::fromLatin1(byteArray.toBase64().data());
}

void WebSocketServer::sendMessage(QString message)
{
    QtWebsocket::QWsSocket* client;
    foreach(client, clients)
    {
        client->write(message);
    }

}

void WebSocketServer::processMessage(QString message)
{
    QtWebsocket::QWsSocket* socket = qobject_cast<QtWebsocket::QWsSocket*>(sender());
    if (socket == 0)
    {
        return;
    }
    std::cout << toReadableAscii(message).toStdString() << std::endl;
    QtWebsocket::QWsSocket* client;
    foreach (client, clients)
    {
        client->write(message);
    }
}

void WebSocketServer::processPong(quint64 elapsedTime)
{
    std::cout << tr("ping: %1 ms").arg(elapsedTime).toStdString() << std::endl;
}

void WebSocketServer::socketDisconnected()
{
    QtWebsocket::QWsSocket* socket = qobject_cast<QtWebsocket::QWsSocket*>(sender());
    if (socket == 0)
    {
        return;
    }
    clients.removeOne(socket);
    socket->deleteLater();
    std::cout << tr("Client disconnected").toStdString() << std::endl;
}




QString WebSocketServer::toReadableAscii(QString string)
{
    string.replace(QRegExp(QLatin1String("[������]")), "������");
    string.replace(QRegExp(QLatin1String("[������]")), "a");
    string.replace(QRegExp(QLatin1String("[���ˣ]")), "E");
    string.replace(QRegExp(QLatin1String("[����]")), "e");
    string.replace(QRegExp(QLatin1String("[����]")), "I");
    string.replace(QRegExp(QLatin1String("[����]")), "i");
    string.replace(QRegExp(QLatin1String("[������]")), "O");
    string.replace(QRegExp(QLatin1String("[����������]")), "o");
    string.replace(QRegExp(QLatin1String("[����]")), "U");
    string.replace(QRegExp(QLatin1String("[�����]")), "u");
    string.replace(QRegExp(QLatin1String("[��]")), "Y");
    string.replace(QRegExp(QLatin1String("[��]")), "y");
    string.replace(QRegExp(QLatin1String("[Ǣ]")), "C");
    string.replace(QLatin1Char('�'), "c");
    string.replace(QLatin1Char('�'), "(C)");
    string.replace(QLatin1Char('�'), "(R)");
    string.replace(QLatin1Char('�'), "<<");
    string.replace(QLatin1Char('�'), ">>");
    string.replace(QLatin1Char('�'), "|");
    string.replace(QLatin1Char('�'), "S");
    string.replace(QLatin1Char('�'), "\"");
    string.replace(QLatin1Char('�'), "-");
    string.replace(QLatin1Char('-'), "-");
    string.replace(QLatin1Char('�'), "-");
    string.replace(QLatin1Char('�'), "^1");
    string.replace(QLatin1Char('�'), "^2");
    string.replace(QLatin1Char('�'), "^3");
    string.replace(QLatin1Char('�'), "+-");
    string.replace(QLatin1Char('�'), "1/4");
    string.replace(QLatin1Char('�'), "1/2");
    string.replace(QLatin1Char('�'), "3/4");
    string.replace(QLatin1Char('�'), "x");
    string.replace(QLatin1Char('�'), "/");
    string.replace(QLatin1Char('�'), "`");
    string.replace(QLatin1Char('�'), ".");
    string.replace(QLatin1Char('�'), ",");
    string.replace(QLatin1Char('�'), "?");
    string.replace(QLatin1Char('�'), "g");
    string.replace(QLatin1Char('�'), "AE");
    string.replace(QLatin1Char('�'), "ae");
    string.replace(QLatin1Char('�'), "D");
    string.replace(QLatin1Char('�'), "N");
    string.replace(QLatin1Char('�'), "n");
    string.replace(QLatin1Char('�'), "D");
    string.replace(QLatin1Char('�'), "d");
    string.replace(QLatin1Char('�'), "B");
    string.replace(QChar(0x20AC), "E");
    int i = string.size();
    while (i--)
    {
        QChar c = string.at(i);
        if (c < 32 || c > 126)
        {
            string[i] = ' ';
        }
    }
    return string;
}

