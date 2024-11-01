QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += multimedia
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameElements\MapElements\defenseunit.cpp \
    GameElements/townworkers.cpp \
    GameElements\MapElements\fence.cpp \
    GameElements\MapElements\building.cpp \
    GameElements\bullet.cpp \
    GameElements\enemy.cpp \
    booster.cpp \
    gamescene.cpp \
    GameElements\health.cpp \
    main.cpp \
    mainmenu.cpp \
    GameElements\player.cpp \
    GameElements\MapElements\townhall.cpp \
    node.cpp \
    view.cpp\

HEADERS += \
    GameElements/MapElements\defenseunit.h \
    GameElements/townworkers.h \
    GameElements\MapElements\fence.h \
    GameElements\MapElements\building.h \
    GameElements\bullet.h \
    GameElements\enemy.h \
    booster.h \
    gamescene.h \
    GameElements\health.h \
    mainmenu.h \
    GameElements\player.h \
    GameElements\MapElements\townhall.h \
    node.h \
    view.h\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    Resources.qrc


