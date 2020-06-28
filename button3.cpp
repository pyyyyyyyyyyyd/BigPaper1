#include "button3.h"
#include <QSize>

Button3::Button3(QString ButtonRoad):QPushButton(0),B3Picture(ButtonRoad)
{
    this->setFixedSize(B3Picture.width(),B3Picture.height());
    this->setStyleSheet("QPushButton{border:Opx}");
    this->setIcon(B3Picture);
    this->setIconSize(QSize(B3Picture.size()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);//设置菜单

    QAction * action1 = new QAction(this);
    action1->setText("tower1");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=]()
    {
        emit tower1();
    });

    QAction * action2 = new QAction(this);
    action2->setText("tower2");
    this->addAction(action2);
    connect(action2,&QAction::triggered,this,[=]()
    {
        emit tower2();
    });

    QAction * action3 = new QAction(this);
    action3->setText("tower3");
    this->addAction(action3);
    connect(action3,&QAction::triggered,this,[=]()
    {
        emit tower3();
    });

}

