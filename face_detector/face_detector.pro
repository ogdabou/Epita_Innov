TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/include/opencv2

LIBS += /usr/lib/libopencv*.so \
        /usr/lib/libQtWebsocket.a

QT += websockets \
     network

SOURCES += \
    myrecognizer.cpp \
    facedetectapp.cpp \
    mvt_detection.cpp \
    myqtgui.cpp \
    colordetector.cpp \
    contourdetector.cpp \
    interestzone.cpp \
    Websocketserver.cpp \
    Client.cpp \
    main.cpp \
    usergui.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml \
    Makefile

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
    QTlsServer.h \
    Client.h \
    usergui.h

