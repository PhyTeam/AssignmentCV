
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core
QT -= gui

CONFIG += c++11 -lopencv

TARGET = DemoAssignment
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    demo.cpp \
    common.cpp

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_flann
LIBS += -lopencv_imgcodecs

HEADERS += \
    demo.h \
    common.h
