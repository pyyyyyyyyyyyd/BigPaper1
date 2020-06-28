#include "towerintro.h"
#include "button.h"
#include "qpainter.h"
#include "mainwindow.h"

TowerIntro::TowerIntro(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);

    Button * quit = new Button(":/button/ButtonQuit.jpg");
    quit->setParent(this);
    quit->move(630,530);//位置
    connect(quit,&QPushButton::clicked,this,[=]()
    {
        MainWindow * mainWindow = new MainWindow;
        this->close();//关闭说明界面
        mainWindow->show();
    });
}

void TowerIntro:: paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap picture(":/cover/towerIntro.png");
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入图片
}
