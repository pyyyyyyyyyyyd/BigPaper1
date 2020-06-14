#include "gamewindow.h"
#include "button.h"

#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);

    Button * setTowerB = new Button(":/button/setTower.jpg");//传入按钮图片
    setTowerB->setParent(this);//放置在主窗口上
    setTowerB->move(90,0);//放置塔的按钮在点处
    connect(setTowerB,&Button::clicked,this,&GameWindow::setTower);//将按钮与下面放置塔的函数setTower连接起来

    Button * setEnemyB =new Button(":/button/setEnemybutton.jpg");//按钮图片
    setEnemyB->setParent(this);//放置在主窗口上
    setEnemyB->move(720,530);//按钮位置
    connect(setEnemyB,&Button::clicked,this,&GameWindow::setEnemy); //将按钮与放入敌人的函数联系起来

    QTimer * timer = new QTimer (this);//计时器
    connect(timer,&QTimer::timeout,this,&GameWindow::updateScene);//计时器与刷新函数相连
    timer->start(10);

}

void GameWindow::paintEvent(QPaintEvent *)//画背景函数
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/GameScene.png");//主界面图片
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入主界面图片

    foreach(Tower * tower, towerList) tower->drawtower(&painter);//画塔
    foreach(Enemy * enemy, enemyList) enemy->drawenemy(&painter);//画敌人
    foreach(Bullet * bullet,bulletList) bullet->drawbullet(&painter);//画按钮
}

void GameWindow::setTower()
{
    Tower * tow = new Tower(QPoint(90,90),":/tower/Tower1.jpg");//初始化tower，在相应位置传入塔图片
    towerList.push_back(tow);//使paintevent找到tower
    update();
    launch(tow->getPoint());
}

void GameWindow::setEnemy()//当按下按钮敌人开始出现，塔开始发射子弹
{
    Enemy * enemy = new Enemy(QPoint(0,280),QPoint(800,280),":/enemy/Enemy.jpg");//初始化enemy，敌人移动路径
    enemyList.push_back(enemy);//pushback使paintevent函数找到enemy，enemy才能动
    enemy->move();
    update();

}

void GameWindow::updateScene()
{
    update();
}

void GameWindow::launch(QPoint starPo)
{
    QPoint startPoint;
    startPoint.setX(starPo.x()+50);
    startPoint.setY(starPo.y()+50);

    Bullet * bullet = new Bullet(startPoint,":/bullet/head.png");
    bulletList.push_back(bullet);
    bullet->move();
    update();
}
