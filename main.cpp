/****************************************************************************
**
** Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebSockets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQuickImageProvider>
#include <QImage>
#include <QtWebSockets/QWebSocket>
#include <QObject>
#include <QQuickPaintedItem>

#include "imagepainter.h"

QT_USE_NAMESPACE

class imageObtainer : public QObject
{
private:
    QWebSocket m_webSocket;
public:
    imageObtainer(){
        QObject::connect(&m_webSocket, &QWebSocket::connected, this, &imageObtainer::onConnected);
        m_webSocket.open(QUrl("ws://192.168.0.160:49154"));
    }
    //! [onConnected]
    void onConnected()
    {
        connect(&m_webSocket, &QWebSocket::textMessageReceived,
                this, &imageObtainer::onTextMessageReceived);
        //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
    }
    //! [onConnected]

    //! [onTextMessageReceived]
    void onTextMessageReceived(QString message)
    {
        qDebug() << "Message received:" << message;
        m_webSocket.close();
    }
};

class ColorImageProvider : public QObject, public QQuickImageProvider
{

public:
    ColorImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
    }


    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override
    {
       int width = 100;
       int height = 50;

       if (size)
          *size = QSize(width, height);
       QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                      requestedSize.height() > 0 ? requestedSize.height() : height);
       pixmap.fill(QColor(id).rgba());
       return pixmap;
    }
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImagePainter>("ImagePainterQml", 1, 0, "ImagePainter");

    QQuickView view;
    QQmlEngine *engine = view.engine();
    engine->addImageProvider("imageTest", new ColorImageProvider);
    view.setSource(QUrl(QStringLiteral("qrc:/qml/qmlwebsocketclient/main.qml")));
    view.show();

    return app.exec();
}

