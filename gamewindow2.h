#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

#include "tower.h"
#include "enemy.h"
#include "bullet.h"

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QList>
#include <QTimer>
#include <QMediaPlayer>

class GameWindow2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow2(QWidget *parent = nullptr); //构造函数
    void paintEvent(QPaintEvent *);//画背景函数
    void initgame();
    void GameOver();
    void setButton();
    void putTowerButton(QPoint ButtonPo);
    void showInfrom(QPainter * painter);

    void setTower(int x, int y, QString road, int rate, int size);//按钮，放塔
    Enemy *chooseEnemy(Tower *tower);
    void launch(QPoint starPo, QPoint targetPo, Enemy * choosedEnemy, QMediaPlayer * player);//发射子弹

    void setEnemy1();
    void setEnemy2();
    void updateScene();//实时更新图片
    void reduceEnemyLife(Enemy * enemy);
    void killEnemy(Enemy * enemy);

private:
    int killed = 0;
    int coin = 25;
    int ToEn1=15;//第一类敌人数
    int NuEn1=0;//已出现第一类敌人数
    int ToEn2=10;
    int NuEn2=0;//第二类


    bool ingame = true;
    bool showedOver = false;//是否已经跳出结束提示

    QTimer * timer;
    QList<Tower*>towerList;//塔
    QList<Enemy*>enemyList;//敌人
    QList<Bullet*>bulletList;//子弹

signals:

public slots:
};

#endif // GAMEWINDOW2_H
