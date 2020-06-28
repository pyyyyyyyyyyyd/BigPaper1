#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint towerpo, QString TowerRoad,int size,int rate);
    void drawtower(QPainter * painter);
    QPoint getPoint();
    int getAttachSize();
    int getAttachRate();

private:
    int attacksize;//攻击半径
    int attackrate;//攻击频率，越大越慢

    QPoint topo;
    QPixmap TowerPicture;

signals:

public slots:

};
#endif // TOWER_H
