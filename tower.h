#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint towerpo, QString TowerRoad);
    void drawtower(QPainter * painter);

    //-----------------------------------------------------------------------
    QPoint getPoint();
    //-------------------------------------------------------

private:
    QPoint topo;
    QPixmap TowerPicture;

signals:

public slots:

};
#endif // TOWER_H
