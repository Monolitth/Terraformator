#-------------------------------------------------
#
# Project created by QtCreator 2018-12-13T22:01:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Terraformator
TEMPLATE = app

LIBS += -L$$PWD/ -lwg
LIBS += -LD:\Qt\5.5\mingw492_32\lib\libQt5OpenGL.a -lopengl32

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    terraformator.cpp \
    appsettings.cpp \
    drawer.cpp \
    world.cpp

HEADERS += \
    wg.h \
    wg_global.h \
    terraformator.h \
    appsettings.h \
    drawer.h \
    world.h \
    preset.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
