#include "bullet.h"
#include "enemy.h"

#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QtMath>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>

Bullet::Bullet(int xi_pos, int yi_pos, int xf_pos, int yf_pos,bool b)
    : xi(xi_pos)
    , xf(xf_pos)
    , yi(yi_pos)
    , yf(yf_pos)
    , boost(b)
{
    damagebullet=20;
    Velocity=20;
    QMediaPlayer *sound = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput();
    sound->setSource(QUrl("qrc:/sounds/Resources/laser.mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);
    sound->play();
    if(boost)
    {
    img = new QPixmap(":/Imgs/Resources/file.png");
    *img = img->scaled(20,20);
    setPixmap(*img);
    Velocity+=10;
    damagebullet+=50;
    setPos(xi_pos, yi_pos);
    }else if(!boost){
    img=new QPixmap(":/Imgs/Resources/bullet.png");
    *img = img->scaled(15, 15);
    setPixmap(*img);
    setPos(xi_pos, yi_pos);}

    // Change with bullet
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(50);


}

void Bullet::Move()
{
        if(y() < 0  || y() > scene()->height() || x() < 0 || x() > scene()->width()) {
            scene()->removeItem(this);
            delete this;
            return;
    }

    double dx = Velocity * (((xf - xi) / sqrt(pow((yf - yi), 2) + pow((xf - xi), 2))));
    double dy = Velocity * (((yf - yi) / sqrt(pow((yf - yi), 2) + pow((xf - xi), 2))));
    setPos(x()+dx, y()+dy);
    CheckCollide();

}
void Bullet::CheckCollide()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
            if (enemy) {
                QMediaPlayer *sound = new QMediaPlayer;
                QAudioOutput *audioOutput = new QAudioOutput();
                sound->setSource(
                    QUrl("qrc:/sounds/Resources/Voicy_Barbarian death cry - Clash of Clans.mp3"));
                sound->setAudioOutput(audioOutput);
                audioOutput->setVolume(0.5);
                sound->play();
                delete this;
                // If the cast was successful, reduce the health of the enemy
                enemy->gethealth()->decreasehealth(damagebullet);
                if (enemy->gethealth()->gethealth() <= 0) {
                    delete enemy;
                }
                return;
            }

            return;
        }else if(typeid(*(colliding_items[i])) == typeid(Booster))
        {
            Booster* boost = dynamic_cast<Booster*> (colliding_items[i]);
            emit BoostHit();
            delete boost;
            delete this;
            return;

        }

    }
}
