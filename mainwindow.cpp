#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button.h"
#include "gamewindow.h"
#include "menu.h"

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

    Button * buttonquit = new Button(":/button/ButtonQuit.jpg");//退出按钮图片
    buttonquit->setParent(this);
    buttonquit->move(320,400);//位置
    connect(buttonquit,&Button::clicked,this,&QMainWindow::close);//退出按钮

    Button * buttonstart =new Button(":/button/ButtonStart.jpg");//开始游戏按钮
    buttonstart->setParent(this);
    buttonstart->move(320,310);//位置
    Menu * menuviewer = new Menu;
    connect(buttonstart,&QPushButton::clicked,this,[=]()//“=”表示可以使用当前类里的所有东西，{}里面是函数实现
    {
        this->close();//关闭主界面
        menuviewer->show();
    });

    //QPushButton *botton = new QPushButton(this);        //this表示出现在主界面上
    //botton->setFixedSize(50,50);                        //按钮大小
    //botton->move(400,300);                              //按钮位置
    //connect(botton,&QPushButton::clicked,this,&QMainWindow::close);//close表示点了之后退出出口

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
