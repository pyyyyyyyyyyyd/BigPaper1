#include "enemy.h"

Enemy::Enemy(QPoint startPo, QPoint targetPo, QString enemyroad):QObject(0),EnemyPicture(enemyroad)
{
    this-> nowPoint = startPo;
    this-> startPoint =startPo;
    this-> targetPoint=targetPo;
}

void Enemy::drawenemy(QPainter * painter)
{
    painter-> drawPixmap(nowPoint,EnemyPicture);
}

void Enemy::move()//使敌人移动
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "nowPoint");
    animation-> setDuration(2000);
    animation-> setStartValue(startPoint);
    animation->setEndValue(targetPoint);
    animation->start();
}

QPoint Enemy::getNowPoint()//读取当前位置
{
    return this->nowPoint;
}

void Enemy::setNowPoint(QPoint po)//设定当前位置
{
    this->nowPoint = po;
}
