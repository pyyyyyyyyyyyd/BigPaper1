#include "menu.h"
#include "button.h"
#include "gamewindow.h"
#include "gamewindow2.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);

    Button * chap1 =new Button(":/button/chap1.jpg");//开始游戏按钮
    chap1->setParent(this);
    chap1->move(200,150);//位置
    connect(chap1,&QPushButton::clicked,this,[=]()//“=”表示可以使用当前类里的所有东西，{}里面是函数实现
    {
        GameWindow * gameviewer = new GameWindow;
        this->close();//关闭主界面
        gameviewer->show();
    });

    Button * chap2 =new Button(":/button/chap2.jpg");//开始游戏按钮
    chap2->setParent(this);
    chap2->move(450,300);//位置
    connect(chap2,&QPushButton::clicked,this,[=]()//“=”表示可以使用当前类里的所有东西，{}里面是函数实现
    {
        GameWindow2 * gameviewer = new GameWindow2;
        this->close();//关闭主界面
        gameviewer->show();
    });
}

void Menu:: paintEvent(QPaintEvent *)//每次开mainwindow时都会调用这个函数
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/MenuCover.png");//主界面图片
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入图片
}
