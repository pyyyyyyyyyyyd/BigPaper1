#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPropertyAnimation>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint nowPoint READ getNowPoint WRITE setNowPoint)

public:
    Bullet(QPoint startPo, QPoint targetPo, QString bulletroad);//构造函数
    void drawbullet(QPainter * painter);//画子弹
    void move();//使其移动的函数
    QPoint getNowPoint();//读取当前位置
    void setNowPoint(QPoint po);//设定当前位置
    bool checkReach();

private:
    QPoint startPoint;//开始位置
    QPoint targetPoint;//目标位置
    QPoint nowPoint;//当前位置
    QPixmap BulletPicture;

signals:
public slots:
};

#endif // BULLET_H
