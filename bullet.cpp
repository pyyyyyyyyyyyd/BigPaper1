#include "bullet.h"

Bullet::Bullet(QPoint startPo, QString bulletroad):QObject(0),BulletPicture(bulletroad)//构造函数
{
    this-> nowPoint = startPo;
    this-> startPoint =startPo;
}

void Bullet::drawbullet(QPainter * painter)//画出子弹
{
    painter-> drawPixmap(nowPoint,BulletPicture);
}

void Bullet::move()//使子弹移动
{
    setTarget();

    QPropertyAnimation * animation = new QPropertyAnimation(this, "nowPoint");
    animation-> setDuration(2000);
    animation-> setStartValue(startPoint);
    animation->setEndValue(targetPoint);
    animation->start();
}

QPoint Bullet::getNowPoint()//读取子弹当前位置
{
    return this->nowPoint;
}

void Bullet::setNowPoint(QPoint po)//设定当前位置
{
    this->nowPoint = po;
}

void Bullet::setTarget()
{
    targetPoint.setX(startPoint.x());
    targetPoint.setY(startPoint.y()+150);
}
