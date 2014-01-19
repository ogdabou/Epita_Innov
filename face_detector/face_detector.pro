TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/include/opencv2

LIBS += /usr/lib/libopencv*.so \
        /usr/lib/libwebsockets.so \
        /usr/lib/libQtWebsocket.a

QT += websockets \
     network

SOURCES += \
    myrecognizer.cpp \
    facedetectapp.cpp \
    main.cpp \
    mvt_detection.cpp \
    myqtgui.cpp \
    colordetector.cpp \
    contourdetector.cpp \
    interestzone.cpp \
    Websocketserver.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml

HEADERS += \
    myrecognizer.hpp \
    mainHeader.hpp \
    facedetectapp.h \
    mvt_detection.h \
    myqtgui.h \
    colordetector.h \
    contourdetector.h \
    interestzone.h \
    Websocketserver.h \
    QWsSocket.h \
    QWsServer.h \
    QWsHandshake.h \
    QWsFrame.h \
    QTlsServer.h

