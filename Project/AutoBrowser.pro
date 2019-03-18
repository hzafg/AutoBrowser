#-------------------------------------------------
#
# Project created by QtCreator 2019-03-07T21:12:42
#
#-------------------------------------------------

QT       += qml quick webengine webenginewidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoBrowser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

SOURCES += \
        main.cpp \
    browserwindow.cpp \
    tabwidget.cpp \
    webpage.cpp \
    browser.cpp \
    webview.cpp \
    scriptloader.cpp \
    logger.cpp \
    runtimecontext.cpp \
    weboperations.cpp

HEADERS += \
    browserwindow.h \
    tabwidget.h \
    webpage.h \
    browser.h \
    webview.h \
    scriptloader.h \
    logger.h \
    runtimecontext.h \
    weboperations.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.txt \
    alert.js \
    qtlogging.ini \
    channel.js \
    app.ini
