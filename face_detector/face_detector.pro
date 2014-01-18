TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/include/opencv2

LIBS += /usr/lib/libopencv*.so

SOURCES += \
    myrecognizer.cpp \
    facedetectapp.cpp \
    main.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml

HEADERS += \
    myrecognizer.hpp \
    mainHeader.hpp \
    facedetectapp.h

