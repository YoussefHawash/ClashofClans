#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    View w(&App);
    return App.exec();
}
