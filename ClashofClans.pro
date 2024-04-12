QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += multimedia
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    building.cpp \
    enemy.cpp \
    gamescene.cpp \
    main.cpp \
    hud.cpp \
    mainmenu.cpp \
    player.cpp

HEADERS += \
    building.h \
    enemy.h \
    gamescene.h \
    hud.h \
    mainmenu.h \
    player.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    Resources.qrc
