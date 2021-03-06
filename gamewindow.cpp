#include "gamewindow.h"
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

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
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

void GameWindow::setButton()//在主窗口上放按钮
{
    QPoint Button1(50,50),Button2(250,50),Button3(450,50),Button4(650,50);
    putTowerButton(Button1);
    putTowerButton(Button2);
    putTowerButton(Button3);
    putTowerButton(Button4);
}

void GameWindow::putTowerButton(QPoint ButtonPo)//放按钮实际操作
{
    Button3 * setTowerB = new Button3(":/button/setTower.jpg");//按钮图片
    setTowerB->setParent(this);//放置在主窗口上
    setTowerB->move(ButtonPo);//放置塔的按钮在点处
    connect(setTowerB,&Button3::tower1,this,[=]()
    {
        if(coin>=5)
        {
            setTower(ButtonPo.x(),90,":/tower/Tower1.jpg",200,600);
            coin = coin -5;
        }

    });//塔1的范围，频率分别是100，600
    connect(setTowerB,&Button3::tower2,this,[=]()
    {
        if(coin>=10)
        {
            setTower(ButtonPo.x(),90,":/tower/Tower2.jpg",300,400);
            coin = coin -10;
        }
    });//塔2的范围，频率分别是200，400
    connect(setTowerB,&Button3::tower3,this,[=]()
    {
        if(coin>=20)
        {
            setTower(ButtonPo.x(),90,":/tower/Tower3.jpg",300,200);
            coin = coin -20;
        }
    });//塔3的范围，频率分别是300，200
}

void GameWindow::paintEvent(QPaintEvent *)//画图函数
{
    QPainter painter(this);//画图工具
    QPixmap picture(":/cover/GameViewer.png");//主界面图片
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

void GameWindow::updateScene()
{
    update();
}

void GameWindow::GameOver()//判断输赢
{
    if(!showedOver)//防止多次跳出窗口
    {
        foreach(Enemy * enemy,enemyList)
        {
            QPoint nowpo = enemy->getNowPoint();
            if(nowpo.x()==800&&enemy->life>0)//如果敌人到达基地
            {
                GameOverWindow * gameover = new GameOverWindow;
                this->close();
                gameover->show();//切换窗口
                showedOver = true;//判断是否已经跳出窗口

                QMediaPlayer * player = new QMediaPlayer;
                player->setMedia(QUrl("qrc:/bgm/GameOver.mp3"));
                player->setVolume(80);
                player->play();//播放音效
                ingame = false;
            }
        }

        if(killed==ToEn1+ToEn2)//如果敌人全部被杀
        {
            Win * winView = new Win;
            this -> close();
            winView -> show();//切换窗口
            showedOver = true;

            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/bgm/Win.mp3"));
            player->setVolume(80);
            player->play();//播放音效
            ingame = false;
        }
    }
}

void GameWindow::showInfrom(QPainter * painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawText(QRect(10,550,100,50),QString("coins: %1").arg(coin));
    painter->drawText(QRect(10,570,100,50),QString("baselife: 1"));
    painter->restore();
}

//Tower----------------------------------------------------------------------------------------------------
void GameWindow::setTower(int x, int y,QString road, int size, int rate)//放塔，发射一系列子弹
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

Enemy* GameWindow::chooseEnemy(Tower* tower)//选择一个敌人
{
    int w=0;
    foreach(Enemy * enemy, enemyList)
    {
        QPoint enemyPo=enemy->getNowPoint();
        int x,y;
        x = enemyPo.x();
        y = enemyPo.y();//敌人坐标
        int _x,_y;
        _x =  tower->getPoint().x();
        _y =  tower->getPoint().y();//塔坐标

        double l;
        l=sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));//计算距离

        if(l<=tower->getAttachSize())//在范围内
        {
            return enemy;
            w=1;
            break;
        }
    }

    if(w==0) return NULL;
}

void GameWindow::launch(QPoint starPo, QPoint targetPo, Enemy *choosedEnemy, QMediaPlayer * player)//发射一个子弹
{
    if(!ingame) return;

    player->setMedia(QUrl("qrc:/bgm/bullet.mp3"));
    player->setVolume(20);
    player->play();//发射子弹的音效

    QPoint startPoint;
    startPoint.setX(starPo.x()+50);
    startPoint.setY(starPo.y()+50);//子弹出发点

    QPoint targetPoint;
    targetPoint.setX(targetPo.x()+50);
    targetPoint.setY(targetPo.y()+50);//子弹目标

    Bullet * bullet = new Bullet(startPoint,targetPoint,":/bullet/bullet.jpg");
    bulletList.push_back(bullet);
    bullet->move();//定义一个子弹并使其移动
    reduceEnemyLife(choosedEnemy);//敌人费血
}

//Enemy----------------------------------------------------------------------------------------------------
void GameWindow::setEnemy1()//放入一个第一类敌人
{
    if(NuEn1>=ToEn1) return;

    Enemy * enemy = new Enemy(QPoint(0,260),QPoint(800,260),":/enemy/Enemy1.png",10);//初始化enemy，敌人移动路径
    enemyList.push_back(enemy);//pushback使enemy到数组中去
    enemy->move();
    NuEn1=NuEn1+1;
}

void GameWindow::setEnemy2()//放入一个第二类敌人
{
    if(NuEn2>=ToEn2) return;

    Enemy * enemy = new Enemy(QPoint(0,260),QPoint(800,260),":/enemy/Enemy2.png",20);//初始化enemy，敌人移动路径
    enemyList.push_back(enemy);//pushback使enemy到数组中去
    enemy->move();
    NuEn2=NuEn2+1;
}

void GameWindow::initgame()//多次调用放入一个敌人的函数
{
    QTimer * timer31 = new QTimer(this);
    connect(timer31, &QTimer::timeout,this,setEnemy1);
    timer31 -> start(2000);//两秒放入敌人1

    QTimer * timer32 = new QTimer(this);
    connect(timer32, &QTimer::timeout,this,setEnemy2);
    timer32 -> start(5000);//五秒放入敌人2
}

void GameWindow::reduceEnemyLife(Enemy *enemy)//敌人被打中后减少生命
{
    enemy->life = enemy->life - 1;
    killEnemy(enemy);
}

void GameWindow::killEnemy(Enemy * enemy)//检查敌人是否死亡，死亡则抹去
{
    if(enemy->life>0) return;

    Q_ASSERT(enemy);
    enemyList.removeOne(enemy);
    delete enemy;

    killed = killed + 1;
    coin = coin+5;
}
