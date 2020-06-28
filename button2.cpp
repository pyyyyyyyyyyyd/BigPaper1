#include "button2.h"
#include <QSize>

Button2::Button2(QString ButtonRoad):QPushButton(0),B2Picture(ButtonRoad)
{   
    this->setFixedSize(B2Picture.width(),B2Picture.height());
    this->setStyleSheet("QPushButton{border:Opx}");
    this->setIcon(B2Picture);
    this->setIconSize(QSize(B2Picture.size()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);//设置菜单

    QAction * action1 = new QAction(this);
    action1->setText("enemy");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=]()
    {
        emit chooseEnemy();
    });

    QAction * action2 = new QAction(this);
    action2->setText("tower");
    this->addAction(action2);
    connect(action2,&QAction::triggered,this,[=]()
    {
        emit chooseTower();
    });

}

