QT += quick websockets

TARGET = qmlwebsocketclient

TEMPLATE = app

CONFIG   -= app_bundle

SOURCES += main.cpp \
    imagepainter.cpp

RESOURCES += data.qrc

OTHER_FILES += qml/qmlwebsocketclient/main.qml

target.path = $$[QT_INSTALL_EXAMPLES]/websockets/qmlwebsocketclient
INSTALLS += target

HEADERS += \
    imagepainter.h

