QT       += core gui
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/abstractView.cpp \
    src/abstractcontroller.cpp \
    src/active.cpp \
    src/character.cpp \
    src/door.cpp \
    src/dungeoncrawler.cpp \
    src/floor.cpp \
    src/graphicalui.cpp \
    src/level.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/passive.cpp \
    src/pit.cpp \
    src/portal.cpp \
    src/ramp.cpp \
    src/startscreen.cpp \
    src/switch.cpp \
    src/terminalui.cpp \
    src/tile.cpp \
    src/wall.cpp

HEADERS += \
    include/abstractView.h \
    include/abstractcontroller.h \
    include/active.h \
    include/character.h \
    include/door.h \
    include/dungeoncrawler.h \
    include/floor.h \
    include/graphicalui.h \
    include/level.h \
    include/mainwindow.h \
    include/passive.h \
    include/pit.h \
    include/portal.h \
    include/ramp.h \
    include/startscreen.h \
    include/switch.h \
    include/terminalui.h \
    include/tile.h \
    include/wall.h

FORMS += \
    mainwindow.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
