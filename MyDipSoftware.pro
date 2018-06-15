#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T18:59:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDipSoftware
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    transformation.cpp \
    movexy.cpp \
    zoomxy.cpp \
    rotateangle.cpp \
    grayimage.cpp \
    thresholdinput.cpp \
    definedfilter.cpp \
    getrect.cpp \
    introtuce.cpp

HEADERS  += mainwindow.h \
    transformation.h \
    movexy.h \
    zoomxy.h \
    rotateangle.h \
    grayimage.h \
    thresholdinput.h \
    definedfilter.h \
    getrect.h \
    introtuce.h

FORMS    += mainwindow.ui \
    movexy.ui \
    zoomxy.ui \
    rotateangle.ui \
    thresholdinput.ui \
    definedfilter.ui \
    getrect.ui \
    introtuce.ui

INCLUDEPATH+= build/include/opencv2 \
               C:/opencv/build/include/opencv  \
               C:/opencv/build/include
CONFIG(debug, debug|release): {
LIBS += -LC:\opencv\build\x64\vc14\bin \
-lopencv_world341
-lopencv_world341d
} else:CONFIG(release, debug|release): {
LIBS += -LC:\opencv\build\x64\vc14\bin \
-lopencv_world341
-lopencv_world341d
}



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world341
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world341d
else:unix: LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world341

INCLUDEPATH += $$PWD/../../opencv/build/x64/vc14
DEPENDPATH += $$PWD/../../opencv/build/x64/vc14

