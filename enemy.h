#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPropertyAnimation>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint nowPoint READ getNowPoint WRITE setNowPoint)//该代码是使动画函数认识我们定义的point，read是读取当前位置，write是改写当前位置

public:
    Enemy(QPoint startPo, QPoint targetPo, QString enemyroad);
    void drawenemy(QPainter * painter);
    void move();//使其移动的函数
    QPoint getNowPoint();//读取当前位置
    void setNowPoint(QPoint po);//设定当前位置

private:
    QPoint startPoint;//开始位置
    QPoint targetPoint;//目标位置
    QPoint nowPoint;//当前位置
    QPixmap EnemyPicture;

signals:
public slots:
};

#endif // ENEMY_H
