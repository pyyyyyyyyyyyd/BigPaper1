#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "tower.h"
#include "enemy.h"

//--------------------------------------------------------
#include "bullet.h"
//---------------------------------------------------------

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *);//画背景函数
    void setTower();//按钮，放塔
    void setEnemy();//按钮，放敌人
    void updateScene();//实时更新图片

    //--------------------------------------------------
    void launch(QPoint starPo);//发射子弹
    //-------------------------------------------------

    explicit GameWindow(QWidget *parent = nullptr); //构造函数

private:
    QList<Tower*>towerList;//塔
    QList<Enemy*>enemyList;//敌人

    //-----------------------------------------------------
    QList<Bullet*>bulletList;//子弹
    bool ingame;
    //-----------------------------------------------------

signals:

public slots:
};

#endif // GAMEWINDOW_H
