#include "hud.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    HUD w(&App);
    return App.exec();
}
