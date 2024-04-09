#include "hud.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HUD w;
    w.show();
    return a.exec();
}
