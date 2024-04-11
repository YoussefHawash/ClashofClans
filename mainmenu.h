#ifndef MAINMENU_H
#define MAINMENU_H
#include <QAudioOutput>
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
    QAudioOutput *Output;
    QLabel *volume_label;
    bool IsFullscreen = 0;
    int volumelevel = 100;
    int level = 1;
    QWidget *mainwindow;
    QWidget *settingswindow;
private slots:
    void checkBoxStateChanged(bool state) { IsFullscreen = state; }
    void sliderValueChanged(int value)
    {
        volume_label->setText(QString("Volume: %1%").arg(value));
        Output->setVolume(double(value) / 100);
        volumelevel = value;
    }
    void comboBoxActivated(int index) { level = index + 1; }

public:
    explicit MainMenu(QAudioOutput *);

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
