QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += multimedia
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameElements/defenseunit.cpp \
    GameElements\fence.cpp \
    GameElements\building.cpp \
    GameElements\bullet.cpp \
    GameElements\enemy.cpp \
    gamescene.cpp \
    GameElements\grass.cpp \
    GameElements\health.cpp \
    main.cpp \
    mainmenu.cpp \
    GameElements\player.cpp \
    GameElements\townhall.cpp \
    view.cpp\

HEADERS += \
    GameElements/defenseunit.h \
    GameElements\fence.h \
    GameElements\building.h \
    GameElements\bullet.h \
    GameElements\enemy.h \
    gamescene.h \
    GameElements\grass.h \
    GameElements\health.h \
    mainmenu.h \
    GameElements\player.h \
    GameElements\townhall.h \
    view.h\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    Resources.qrc


