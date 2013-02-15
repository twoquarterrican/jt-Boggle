#-------------------------------------------------
#
# Project created by QtCreator 2013-02-12T08:46:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jt-Boggle
TEMPLATE = app


SOURCES += main.cpp\
    boggleboard.cpp \
    boggleWindow.cpp \
    bogglegameplay.cpp \
    lexicon.cpp \
    bogglecube.cpp

HEADERS  += \
    boggleboard.h \
    boggleWindow.h \
    bogglegameplay.h \
    boggleconstants.h \
    sleep.h \
    lexicon.h \
    bogglecube.h

OTHER_FILES += \
    EnglishWords.dat \
    test.txt \
    en_US.dic \
    dict.txt

RESOURCES += \
    dictionary.qrc

