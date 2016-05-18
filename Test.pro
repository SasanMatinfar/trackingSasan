#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T11:38:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    opencvqtconvert.cpp

HEADERS  += widget.h \
    opencvqtconvert.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opencv/opencv/build/x64/vc14/lib/ -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opencv/opencv/build/x64/vc14/lib/ -lopencv_world310d
else:unix: LIBS += -L$$PWD/../../../../opencv/opencv/build/x64/vc14/lib/ -lopencv_world310

INCLUDEPATH += C:/opencv/opencv/build/include
DEPENDPATH += C:/opencv/opencv/build/include
