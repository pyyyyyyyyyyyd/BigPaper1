#include "button.h"
#include <QPixmap>

Button::Button(QString ButtonRoad) : QPushButton(0)
{
    QPixmap road(ButtonRoad);
    this->setFixedSize(road.width(),road.height());//按钮大小=图片大小
    this->setStyleSheet("QPushButton{border:Opx;}");//根据图片外观调整自己外观
    this->setIcon(road);//设一个图标并传入图片
    this->setIconSize(QSize(road.width(),road.height()));//图标大小与图片大小保持一致

}
