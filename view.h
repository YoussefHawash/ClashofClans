#ifndef VIEW_H
#define VIEW_H
#include <QApplication>
#include <QAudioOutput>
#include <QBoxLayout>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QPushButton>
#include <QSizePolicy>

#include "gamescene.h"
#include "mainmenu.h"
class View : public QGraphicsView
{
    Q_OBJECT
private:
    QApplication *App;
    MainMenu *MainUI;
    GameScene *gamescene;
    QMediaPlayer *Sound;
    QAudioOutput *audioOutput;

public:
    View(QApplication * = nullptr);
    void DisplayMainMenu();
    ~View();

public slots:
    void NewGame();
    void RandomGame();
    void StoryMode();
    void Exit();
};
#endif // VIEW_H
