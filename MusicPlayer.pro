#-------------------------------------------------
#
# Project created by QtCreator 2023-06-27T01:26:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer
TEMPLATE = app

SOURCES += main.cpp\
        mymain.cpp \
    favouritemusicdatabase.cpp \
    musicinfo.cpp \
    soundvolume.cpp \
    lyricshandle.cpp \
    pictureitem.cpp \
    picturebutton.cpp \
    pictureslideshow.cpp

HEADERS  += mymain.h \
    favouritemusicdatabase.h \
    musicinfo.h \
    soundvolume.h \
    lyricshandle.h \
    pictureitem.h \
    picturebutton.h \
    pictureslideshow.h

FORMS    += mymain.ui \
    musicinfo.ui \
    soundvolume.ui \
    pictureslideshow.ui

RESOURCES += \
    res.qrc
LIBS += -L/usr/lib/x86_64-linux-gnu -lmysqlclient
