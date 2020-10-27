#include "imagepainter.h"
#include <QPainter>
#include <QImage>

// https://www.nuomiphp.com/eplan/en/70207.html
// https://stackoverflow.com/questions/59470754/qt-quick-how-to-use-a-c-class-inheriting-from-qquickpainteditem-in-a-qml-int
ImagePainter::ImagePainter(QQuickItem* parent)
{
    img = QImage(10,10, QImage::Format_RGB888);
    m_webSocket.open(QUrl("ws://192.168.0.160:49154"));
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &ImagePainter::onBinaryMessageReceived);
    connect(&m_webSocket, &QWebSocket::disconnected,
            this, &ImagePainter::onDisconnected);
}


void ImagePainter::paint(QPainter* painter)
{
    qDebug("paiting");
    painter->drawImage(0,0,img);
}

void ImagePainter::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    color = message;
    update();
}

void ImagePainter::onBinaryMessageReceived(QByteArray array){
    //qDebug("Binary received");
    img.loadFromData(QByteArray::fromBase64(array));
    update();
}

void ImagePainter::onConnected()
{
    qDebug("Connected");
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ImagePainter::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &ImagePainter::onBinaryMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void ImagePainter::onDisconnected()
{
    m_webSocket.open(QUrl("ws://192.168.0.160:49152"));
}
