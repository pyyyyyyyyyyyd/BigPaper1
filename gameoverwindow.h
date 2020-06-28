#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>

class GameOverWindow : public QMainWindow
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent *event);
    explicit GameOverWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // GAMEOVERWINDOW_H
