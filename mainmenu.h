#ifndef MAINMENU_H
#define MAINMENU_H
#include <QAudioOutput>
#include <QCheckBox>
#include <QComboBox>
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
    bool IsFullscreen;
    int volumelevel;
    int level;
    QAudioOutput *Output;
    QLabel *volume_label;
    QWidget *mainwindow;
    QWidget *gameswindow;
    QWidget *settingswindow;

public:
    explicit MainMenu(QAudioOutput *);
    void SetMainWindow();
    void SetGamesWindow();
    void SetSettingsWindow();
    void ShowMainWindow();
    void ShowGamesWindow();
    void ShowSettingsWindow();
    bool fullscreen();
signals:
    void exit();
    void newgame();
    void randomgame();
    void storymode();
private slots:
    void checkBoxStateChanged(bool);
    void sliderValueChanged(int);
    void comboBoxActivated(int);
};

#endif // MAINMENU_H
