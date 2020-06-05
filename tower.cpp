#include "tower.h"

#include <QPoint>
#include <QPixmap>
#include <QPainter>

Tower::Tower(QPoint towerpo, QString TowerRoad):QObject(0),TowerPicture(TowerRoad)
{
    topo=towerpo;
}

void Tower::drawtower(QPainter * painter)
{
    painter->drawPixmap(topo,TowerPicture);
}

//------------------------------------------------------------------------------
QPoint Tower::getPoint()
{
    return this->topo;
}
//-------------------------------------------------------------------------------
