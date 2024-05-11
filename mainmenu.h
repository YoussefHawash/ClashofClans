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
    bool fullscreen;
    int volumelevel, gamelevel;
    QAudioOutput *Output;
    QLabel *volume_label;
    QWidget *mainwindow;
    QWidget *gameswindow;
    QWidget *settingswindow;

public:
    MainMenu(QAudioOutput *);
    ~MainMenu();
    //SetUp Ui
    void SetMainMenuContainer();
    void SetGamesContainer();
    void SetSettingsContainer();
    //Toggling Between Widnows
    void ShowMainMenu();
    void ShowGames();
    void ShowSettings();
    //Getters
    bool IsFullscreen() const;

signals:
    void newgame(int);
    void exit();
private slots:
    void Emit_NEWGAME() { emit newgame(gamelevel); };
    void checkBoxStateChanged(bool);
    void sliderValueChanged(int);
    void comboBoxActivated(int);
};

#endif // MAINMENU_H
