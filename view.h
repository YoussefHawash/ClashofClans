#ifndef VIEW_H
#define VIEW_H
#include <QApplication>
#include <QAudioOutput>
#include <QBoxLayout>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QSizePolicy>

#include "gamescene.h"
#include "mainmenu.h"

class View : public QGraphicsView
{
    Q_OBJECT
private:
    QApplication *App;
    MainMenu *MainUI;
    QMediaPlayer *Sound;
    QAudioOutput *audioOutput;
public:
    View(QApplication * = nullptr);
    void DisplayGameMenu();
    ~View();

public slots:
    void NewGame(int);
    void ReturnToMainMenu();
    void Exit();
};
#endif // VIEW_H
