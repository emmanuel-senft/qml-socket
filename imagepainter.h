#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H
#include <QQuickPaintedItem>
#include <QtWebSockets/QWebSocket>
#include <QImage>

class ImagePainter : public QQuickPaintedItem
{
    Q_OBJECT
private:
    QWebSocket m_webSocket;
    QImage img;
    QString color;
public:
    ImagePainter(QQuickItem* parent = 0);

    void paint(QPainter* painter);

    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray array);
};

#endif // IMAGEPAINTER_H
/*
class imagePainter : public QQuickPaintedItem
{
    Q_OBJECT
private:
    QWebSocket m_webSocket;
public:
    imagePainter(QQuickItem* parent = 0){
        QObject::connect(&m_webSocket, &QWebSocket::connected, this, &imagePainter::onConnected);
        m_webSocket.open(QUrl("ws://192.168.0.160:49154"));
    }
    ~imagePainter(){ };
    //! [onConnected]
    void onConnected()
    {
        connect(&m_webSocket, &QWebSocket::textMessageReceived,
                this, &imagePainter::onTextMessageReceived);
        //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
    }
    //! [onConnected]

    //! [onTextMessageReceived]
    void onTextMessageReceived(QString message)
    {
        qDebug() << "Message received:" << message;
        m_webSocket.close();
    }
    void paint(QPainter *painter) override;
};
*/
