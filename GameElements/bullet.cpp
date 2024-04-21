#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QtMath>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>

using namespace std;



Bullet::Bullet(int xi_pos,int yi_pos,int xf_pos,int yf_pos)
{
    xi=xi_pos;
    yi= yi_pos;
    xf= xf_pos;
    yf=  yf_pos;
    setBrush(Qt::red);
    setRect(xi_pos,yi_pos,15,10);
    QMediaPlayer *sound = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput();
    sound->setSource(QUrl("qrc:/sounds/Resources/bom.mp3 (online-audio-converter.com).mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);
    sound->play();



    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (shoot()));
    timer->start(50);
}

void Bullet::shoot()
{
    const int Vel = 20;



    double dx = Vel*(((xf-xi)/sqrt(pow((yf-yi),2)+pow((xf-xi),2))));

    double dy = Vel*(((yf-yi)/sqrt(pow((yf-yi),2)+pow((xf-xi),2))));

    setPos(x()+dx, y()+dy);

    QList<QGraphicsItem *>colliding_items =collidingItems();
    for(int i=0,n=colliding_items.size();i<n;++i)
    {
        if(typeid(*(colliding_items[i]))== typeid(Enemy))
        {
            Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
            if (enemy) {
                // If the cast was successful, reduce the health of the enemy
                enemy->getdamage(200);
                delete this;
            }
            QMediaPlayer *sound = new QMediaPlayer;
            QAudioOutput *audioOutput = new QAudioOutput();
            sound->setSource(QUrl("qrc:/sounds/Resources/Voicy_Barbarian death cry - Clash of Clans.mp3"));
            sound->setAudioOutput(audioOutput);
            audioOutput->setVolume(0.5);
            sound->play();

            return;
        }
    }
    //     if(y() < 0  || y() > scene()->height() || x() < 0 || x() > scene()->width()) {
    //     qDebug() << y();
    //         scene()->removeItem(this);
    //         delete this;
    // }
}
