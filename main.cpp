#include "mainwindow.h"
#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/bgm/Tower.mp3"));
    player->setVolume(80);
    player->play();

    return a.exec();
}
