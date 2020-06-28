#ifndef WIN_H
#define WIN_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>

class Win: public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *event);
    explicit Win(QWidget *parent = nullptr);

signals:

public slots:
};


#endif // WIN_H
