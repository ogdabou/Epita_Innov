TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/include/opencv2

LIBS += /usr/lib/libopencv*.so

SOURCES += main.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml

