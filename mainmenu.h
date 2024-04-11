#ifndef MAINMENU_H
#define MAINMENU_H
#include <QCheckBox>
#include <QComboBox>
#include <QFrame>
#include <QIcon>
#include <QLabel>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
class MainMenu : public QMainWindow
{
    Q_OBJECT
private:
    QCheckBox *fullscreen_check;
    QSlider *volume;
    QComboBox *levels;
    bool IsFullscreen = 0;
    int volumelevel = 100;
    int level = 1;
    QWidget *mainwindow;
    QWidget *settingswindow;

public:
    explicit MainMenu(QWidget *parent = nullptr);

    void ClearScene();
    bool fullscreen();
    void SetSettings();
    void ShowSettings();
    void SetMainMenu();
    void ShowMainMenu();
signals:
    void exit();
    void play();
};

#endif // MAINMENU_H
