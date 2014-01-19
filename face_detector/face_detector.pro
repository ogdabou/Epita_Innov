TEMPLATE = app
CONFIG += console
CONFIG += qt

INCLUDEPATH += /usr/include/opencv2

LIBS += /usr/lib/libopencv*.so

SOURCES += \
    myrecognizer.cpp \
    facedetectapp.cpp \
    main.cpp \
    mvt_detection.cpp \
    myqtgui.cpp

OTHER_FILES += \
    haarcascade_frontalface_default.xml

HEADERS += \
    myrecognizer.hpp \
    mainHeader.hpp \
    facedetectapp.h \
    mvt_detection.h \
    myqtgui.h

