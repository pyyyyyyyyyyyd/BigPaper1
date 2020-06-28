#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"
#include "button2.h"
#include "gamewindow.h"
#include "menu.h"
#include "enemyintro.h"
#include "towerintro.h"

#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600);//设定窗口大小
    ui->setupUi(this);

    Button * buttonquit = new Button(":/button/ButtonQuit.jpg");//退出按钮
    buttonquit->setParent(this);
    buttonquit->move(320,400);//位置
    connect(buttonquit,&Button::clicked,this,&QMainWindow::close);

    Button * buttonstart =new Button(":/button/ButtonStart.jpg");//开始游戏按钮
    buttonstart->setParent(this);
    buttonstart->move(320,310);//位置
    Menu * menuviewer = new Menu;
    connect(buttonstart,&QPushButton::clicked,this,[=]()
    {
        this->close();//关闭主界面
        menuviewer->show();
    });//“=”表示可以使用当前类里的所有东西，{}里面是函数实现

    Button2 * buttonintro = new Button2(":/button/ButtoIntroduction.jpg");//游戏介绍按钮
    buttonintro->setParent(this);
    buttonintro->move(320,220);
    connect(buttonintro,&Button2::chooseEnemy,this,[=]()
    {
        EnemyIntro * enIn = new EnemyIntro;
        this->close();
        enIn->show();
    });
    connect(buttonintro,&Button2::chooseTower,this,[=]()
    {
        TowerIntro * toIn = new TowerIntro;
        this->close();
        toIn->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: paintEvent(QPaintEvent *)//每次开mainwindow时都会调用这个函数
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/TowCover.jpg");//主界面图片
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入图片
}
