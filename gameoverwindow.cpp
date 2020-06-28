#include "gameoverwindow.h"

GameOverWindow::GameOverWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);
}

void GameOverWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/GameOver.jpg");//主界面图片
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入图片
}
