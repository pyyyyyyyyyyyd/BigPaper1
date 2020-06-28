#ifndef BUTTON3_H
#define BUTTON3_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QAction>

class Button3 : public QPushButton
{
    Q_OBJECT
public:
    Button3(QString ButtonRoad);
private:
    QPixmap B3Picture;

signals:
    void tower1();
    void tower2();
    void tower3();

public slots:
};

#endif // BUTTON3_H
