#include "tower.h"

#include <QPoint>
#include <QPixmap>
#include <QPainter>

Tower::Tower(QPoint towerpo, QString TowerRoad, int size, int rate):QObject(0),TowerPicture(TowerRoad)
{
    topo=towerpo;
    attackrate = rate;
    attacksize = size;
}

void Tower::drawtower(QPainter * painter)
{
    painter->drawPixmap(topo,TowerPicture);//画出塔

    painter->setPen(Qt::white);
    painter->drawEllipse(topo, attacksize, attacksize);//画出攻击范围

}

QPoint Tower::getPoint()
{
    return this->topo;
}

int Tower::getAttachSize()
{
    return this->attacksize;
}

int Tower::getAttachRate()
{
    return this -> attackrate;
}
