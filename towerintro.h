#ifndef TOWERINTRO_H
#define TOWERINTRO_H

#include <QMainWindow>

class TowerIntro : public QMainWindow
{
    Q_OBJECT
public:
    explicit TowerIntro(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // TOWERINTRO_H
