#ifndef HUD_H
#define HUD_H

#include <QMainWindow>

class HUD : public QMainWindow
{
    Q_OBJECT

public:
    HUD(QWidget *parent = nullptr);
    ~HUD();
};
#endif // HUD_H
