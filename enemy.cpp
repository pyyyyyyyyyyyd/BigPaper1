#include "enemy.h"

Enemy::Enemy(QPoint startPo, QPoint targetPo, QString enemyroad, int life):QObject(0),EnemyPicture(enemyroad)
{
    this-> nowPoint = startPo;
    this-> startPoint =startPo;
    this-> targetPoint=targetPo;
    this->life = life;
}

void Enemy::drawenemy(QPainter * painter)
{
    static const int LifeWide = 60;

    QPoint lifeBarPoint = nowPoint + QPoint(0,-10);
    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);
    QRect TotallifeBarRect (lifeBarPoint+QPoint(0,-10), QSize(LifeWide, 2));
    painter->drawRect(TotallifeBarRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect (lifeBarPoint, QSize((double)life / MaxLife * LifeWide, 2));
    if(life>=0) painter->drawRect(healthBarRect);

    painter-> drawPixmap(nowPoint,EnemyPicture);
}

void Enemy::move()//使敌人移动
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "nowPoint");
    animation-> setDuration(10000);//速度，越大越慢（移动时间）
    animation-> setStartValue(startPoint);
    animation->setEndValue(targetPoint);
    animation->start();
}

void Enemy::move2()
{
    if(nowPoint.x()<235 && nowPoint.y()==25) nowPoint.setX(nowPoint.x()+5);
    if(nowPoint.x()==235 && nowPoint.y()<525) nowPoint.setY(nowPoint.y()+5);
    if(nowPoint.x()<550 && nowPoint.y()==525) nowPoint.setX(nowPoint.x()+5);
    if(nowPoint.x()==550 && nowPoint.y()>230) nowPoint.setY(nowPoint.y()-5);
    if(nowPoint.x()<800 && nowPoint.x()>=550 && nowPoint.y()==230) nowPoint.setX(nowPoint.x()+5);
}

QPoint Enemy::getNowPoint()//读取当前位置
{
    return this->nowPoint;
}

void Enemy::setNowPoint(QPoint po)//设定当前位置
{
    this->nowPoint = po;
}

