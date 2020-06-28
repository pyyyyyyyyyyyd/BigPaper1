#ifndef ENEMYINTRO_H
#define ENEMYINTRO_H

#include <QMainWindow>

class EnemyIntro : public QMainWindow
{
    Q_OBJECT
public:
    explicit EnemyIntro(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // ENEMYINTRO_H
