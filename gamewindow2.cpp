#include "gamewindow2.h"
#include "button.h"
#include "button3.h"
#include "gameoverwindow.h"
#include "win.h"

#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QMediaPlayer>
#include <QRect>


GameWindow2::GameWindow2(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(800,600);
    setButton();//在窗口上放置按钮
    initgame();//开始放入敌人

    timer = new QTimer (this);//计时器
    connect(timer,&QTimer::timeout,this,[=]()
    {
        updateScene();
        GameOver();
    });//计时器与刷新函数,检测结束函数相连
    timer->start(10);
}

void GameWindow2::setButton()//在主窗口上放按钮
{
    QPoint Button1(40,150),Button2(50,300),Button3(50,480),Button4(360,50),Button5(370,210),Button6(370,390),Button7(550,110),Button8(700,110),Button9(680,385),Button10(680,525);//按钮
    putTowerButton(Button1);
    putTowerButton(Button2);
    putTowerButton(Button3);
    putTowerButton(Button4);
    putTowerButton(Button5);
    putTowerButton(Button6);
    putTowerButton(Button7);
    putTowerButton(Button8);
    putTowerButton(Button9);
    putTowerButton(Button10);
}

void GameWindow2::putTowerButton(QPoint ButtonPo)//放按钮具体操作
{
    Button3 * setTowerB = new Button3(":/button/setTower2.jpg");//按钮图片
    setTowerB->setParent(this);//放置在主窗口上
    setTowerB->move(ButtonPo);//放置塔的按钮在点处
    connect(setTowerB,&Button3::tower1,this,[=]()
    {
        if(coin>=5)
        {
            setTower(ButtonPo.x(),ButtonPo.y()-20,":/tower/Tower1.jpg",200,600);
            coin = coin -5;
        }
    });//塔1的范围，频率分别是100，600
    connect(setTowerB,&Button3::tower2,this,[=]()
    {
        if(coin>=10)
        {
            setTower(ButtonPo.x(),ButtonPo.y()-20,":/tower/Tower2.jpg",300,400);
            coin = coin -10;
        }
    });//塔2的范围，频率分别是200，400
    connect(setTowerB,&Button3::tower3,this,[=]()
    {
        if(coin>=20)
        {
            setTower(ButtonPo.x(),ButtonPo.y()-20,":/tower/Tower3.jpg",300,200);
            coin = coin -20;
        }
    });//塔3的范围，频率分别是300，200
}

void GameWindow2::paintEvent(QPaintEvent *)//画图函数
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/GameViewer2.png");//主界面图片
    painter.drawPixmap(0,0,this->width(),this->height(),picture);//传入主界面图片

    showInfrom(&painter);

    foreach(Tower * tower, towerList) tower->drawtower(&painter);//画塔
    foreach(Enemy * enemy, enemyList) //画敌人
    {
        //if(enemy->life>0) enemy->drawenemy(&painter);
        enemy->drawenemy(&painter);
    }
    foreach(Bullet * bullet,bulletList)//画子弹
    {
        if(!bullet->checkReach())
        bullet->drawbullet(&painter);
    }
}

void GameWindow2::updateScene()
{
    update();
}

void GameWindow2::GameOver()//判断输赢
{
    if(!showedOver)
    {
        foreach(Enemy * enemy,enemyList)
        {
            QPoint nowpo = enemy->getNowPoint();
            if(nowpo.x()==800&&enemy->life>0)
            {
                GameOverWindow * gameover = new GameOverWindow;
                this->close();
                gameover->show();
                showedOver = true;

                QMediaPlayer * player = new QMediaPlayer;
                player->setMedia(QUrl("qrc:/bgm/GameOver.mp3"));
                player->setVolume(80);
                player->play();
                ingame = false;
            }
        }

        if(killed==ToEn1+ToEn2)
        {
            Win * winView = new Win;
            this -> close();
            winView -> show();
            showedOver = true;

            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/bgm/Win.mp3"));
            player->setVolume(80);
            player->play();
            ingame = false;
        }
    }
}

void GameWindow2::showInfrom(QPainter * painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawText(QRect(10,550,100,50),QString("coins: %1").arg(coin));
    painter->drawText(QRect(10,570,100,50),QString("baselife: 1"));
    painter->restore();
}

//Tower----------------------------------------------------------------------------------------------------
void GameWindow2::setTower(int x, int y,QString road, int size, int rate)//放塔，发射一系列子弹
{
    Tower * tow = new Tower(QPoint(x,y),road,size,rate);//初始化tower
    towerList.push_back(tow);//使paintevent找到tower
    update();

    QTimer * timer1 = new QTimer (this);//设置定时器
    QMediaPlayer * player = new QMediaPlayer;
    connect(timer1,&QTimer::timeout,this,[=]()
    {
        if(chooseEnemy(tow)!=NULL)
        {
            Enemy * choosedEn = chooseEnemy(tow);
            launch(tow->getPoint(),choosedEn->getNowPoint(),choosedEn,player);
        }
    });//将定时器与发射一个子弹的函数连接，从而发射一系列子弹
    timer1->start(tow->getAttachRate());//发射子弹的时间间隔
}

Enemy* GameWindow2::chooseEnemy(Tower* tower)//选择一个敌人
{
    int w=0;
    foreach(Enemy * enemy, enemyList)
    {
        QPoint enemyPo=enemy->getNowPoint();
        int x,y;
        x = enemyPo.x();
        y = enemyPo.y();
        int _x,_y;
        _x =  tower->getPoint().x();
        _y =  tower->getPoint().y();

        double l;
        l=sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));

        if(l<=tower->getAttachSize())
        {
            return enemy;
            w=1;
            break;
        }
    }

    if(w==0) return NULL;
}

void GameWindow2::launch(QPoint starPo, QPoint targetPo, Enemy *choosedEnemy, QMediaPlayer * player)//发射一个子弹
{
    if(!ingame) return;

    player->setMedia(QUrl("qrc:/bgm/bullet.mp3"));
    player->setVolume(20);
    player->play();

    QPoint startPoint;
    startPoint.setX(starPo.x()+50);
    startPoint.setY(starPo.y()+50);

    QPoint targetPoint;
    targetPoint.setX(targetPo.x()+50);
    targetPoint.setY(targetPo.y()+50);

    Bullet * bullet = new Bullet(startPoint,targetPoint,":/bullet/bullet.jpg");
    bulletList.push_back(bullet);
    bullet->move();//定义一个子弹并使其移动
    reduceEnemyLife(choosedEnemy);
}

//Enemy----------------------------------------------------------------------------------------------------
void GameWindow2::setEnemy1()//放入一个第一类敌人
{
    if(NuEn1>=ToEn1) return;

    Enemy * enemy = new Enemy(QPoint(0,25),QPoint(800,230),":/enemy/Enemy1.png",20);//初始化enemy，敌人移动路径
    enemyList.push_back(enemy);//pushback使enemy到数组中去

    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]()
    {
        enemy->move2();
    });
    timer->start(100);

    NuEn1=NuEn1+1;
}

void GameWindow2::setEnemy2()//放入一个第二类敌人
{
    if(NuEn2>=ToEn2) return;

    Enemy * enemy = new Enemy(QPoint(0,25),QPoint(800,230),":/enemy/Enemy2.png",40);//初始化enemy，敌人移动路径
    enemyList.push_back(enemy);//pushback使enemy到数组中去

    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=]()
    {
        enemy->move2();
    });
    timer->start(100);

    NuEn2=NuEn2+1;

}

void GameWindow2::initgame()//多次调用放入一个敌人的函数
{
    QTimer * timer31 = new QTimer(this);
    connect(timer31, &QTimer::timeout,this,setEnemy1);
    timer31 -> start(5000);//两秒放入敌人1

    QTimer * timer32 = new QTimer(this);
    connect(timer32, &QTimer::timeout,this,setEnemy2);
    timer32 -> start(7000);//五秒放入敌人2
}

void GameWindow2::reduceEnemyLife(Enemy *enemy)//敌人被打中后减少生命
{
    enemy->life = enemy->life - 1;
    killEnemy(enemy);
}

void GameWindow2::killEnemy(Enemy * enemy)//检查敌人是否死亡，死亡则抹去
{
    if(enemy->life>0) return;

    Q_ASSERT(enemy);
    enemyList.removeOne(enemy);
    delete enemy;

    killed = killed + 1;
    coin = coin+5;
}
