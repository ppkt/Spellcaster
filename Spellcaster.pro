#-------------------------------------------------
#
# Project created by QtCreator 2011-10-10T19:49:09
#
#-------------------------------------------------

QT       += core gui

TARGET = Spellcaster
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS    += -L"C:\\Users\\ppkt\\Desktop\\qwt-6.0.1\\lib" -lqwtd
}

CONFIG(release, debug|release) {
    LIBS    += -L"C:\\Users\\ppkt\\Desktop\\qwt-6.0.1\\lib" -lqwt
}

INCLUDEPATH += "C:\\Users\\ppkt\\Desktop\\qwt-6.0.1\\src"

SOURCES += main.cpp\
        spellcaster.cpp \
    parser.cpp \
    config.cpp \
    previewwidget.cpp

HEADERS  += spellcaster.h \
    parser.h \
    config.h \
    qtriple.h \
    previewwidget.h

FORMS    += spellcaster.ui

OTHER_FILES += \
    template.txt










