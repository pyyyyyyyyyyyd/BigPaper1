#ifndef BUTTON2_H
#define BUTTON2_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QAction>

class Button2 : public QPushButton
{
    Q_OBJECT
public:
    Button2(QString ButtonRoad);
private:
    QPixmap B2Picture;

signals:
    void chooseEnemy();
    void chooseTower();

public slots:
};

#endif // BUTTON2_H
