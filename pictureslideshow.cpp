#include "pictureslideshow.h"
#include "ui_pictureslideshow.h"
#include <QDebug>
#include "pictureitem.h"
#include <QSize>
#include <unistd.h>
#include <QBitmap>
#include <QTimer>
#define PICTURE_NUM 4
#define GRAPH_VIEW_SIZE QSize(471, 141)
static QList<pictureItem *> itemList;
#define P1 (qreal)0.00
#define P2 (qreal)0.15
#define P3 (qreal)0.45
#define P4 (qreal)0.15


PictureSlideShow::PictureSlideShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureSlideShow),
    m_scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    setButtonGroup();
    setInitList();
    setSlides();
    PictureButtonAndPictureItemConnections();
    connect(ui->pushButton_rightview,&QPushButton::clicked, this, &PictureSlideShow::rollNextItem);
    connect(ui->pushButton_leftview, &QPushButton::clicked, this, &PictureSlideShow::rollPrevItem);

    QIcon iconForward(":/image/forward.png");
    ui->pushButton_rightview->setStyleSheet("border-radius:12px;}");
    QPixmap pixmap = iconForward.pixmap(iconForward.actualSize(QSize(48, 48)));
    pixmap.setMask(pixmap.createMaskFromColor(Qt::white));
    ui->pushButton_rightview->setIcon(QIcon(pixmap));

    QIcon iconBack(":/image/back.png");
    ui->pushButton_leftview->setStyleSheet("border-radius:12px;}");
    QPixmap pixmapBack = iconBack.pixmap(iconBack.actualSize(QSize(48, 48)));
    pixmapBack.setMask(pixmapBack.createMaskFromColor(Qt::white));
    ui->pushButton_leftview->setIcon(QIcon(pixmapBack));

    timer->start(4000);
    connect(timer, &QTimer::timeout, this, &PictureSlideShow::rollNextItem);
}

void PictureSlideShow::setButtonGroup()
{
    buttongroup = new QButtonGroup(this);
    buttongroup->addButton(ui->picButton1, 0);
    buttongroup->addButton(ui->picButton2, 1);
    buttongroup->addButton(ui->picButton3, 2);
    buttongroup->addButton(ui->picButton4, 3);
    buttongroup->setExclusive(true);
    buttongroup->button(1)->setChecked(true);
    for(int i = 0; i < PICTURE_NUM; i++){
        static_cast<pictureButton *> (buttongroup->button(i))->setId(i);
    }
    qDebug() << ui->picButton4->id() << endl;
}

void PictureSlideShow::setInitList()
{
    m_PointList << P1 << P2<< P3 << P4;
    m_ZValueList << 1 << 2 << 1  << 0;
    m_PixmapScaleList << 1<< 1.2 << 1 << 1;
}

void PictureSlideShow::PictureButtonAndPictureItemConnections()
{
    for(int i = 0; i < PICTURE_NUM; i++){
        void (pictureButton:: *p)(int) = &pictureButton::entered;
        connect(static_cast<pictureButton *> (buttongroup->button(i)), p, this,  &PictureSlideShow::rollItem);
    }

}


void PictureSlideShow::setSlides()
{
        ui->graphicsView->setStyleSheet("background: transparent; padding: 0px; border: 0px;");
        ui->graphicsView->setScene(m_scene);
        m_scene->setSceneRect(0,0,GRAPH_VIEW_SIZE.width(),GRAPH_VIEW_SIZE.height());

        m_MidLine.setPoints(QPointF(0,0),QPointF(GRAPH_VIEW_SIZE.width(),0));

        //Add corresponding image
        for (int i = 1; i<=PICTURE_NUM;i++) {
            m_PixmapList.append(QPixmap(QString(":/image/slides/slide%1.png").arg(i)));
        }
        for (int i = 0; i< PICTURE_NUM;i++) {
            itemList.append(new pictureItem(m_PixmapList[i].scaled(GRAPH_VIEW_SIZE,
                                   Qt::KeepAspectRatio,Qt::SmoothTransformation)));
            itemList[i]->setScale(m_PixmapScaleList[i]);
            itemList[i]->setItemId(i);
            itemList[i]->setOffset(QPointF(0,0)); //offset in coordinates (i.e where to show the images)
        }
        for(int i = 0; i<PICTURE_NUM; i++)
        {
            m_scene->addItem(itemList[i]);
            itemList[i]->setPos(m_MidLine.pointAt(m_PointList[i]));//setting slide position
            itemList[i]->setZValue(m_ZValueList[i]);//setting slide priority
            itemList[i]->setTransformationMode(Qt::SmoothTransformation);

        }
        currentMainSlideID = 1;

}

PictureSlideShow::~PictureSlideShow()
{
    delete ui;
}

void PictureSlideShow::rollItem(int id)
{
    int mainSlidePos = 1;
    int j = mainSlidePos;
    while(id != currentMainSlideID){
        for(; j < PICTURE_NUM; j++){
            pictureItem *temp = itemList[j];
            itemList[j] = itemList[j - 1];
            itemList[j - 1] = temp;
        }
        j = mainSlidePos;
        currentMainSlideID = itemList[mainSlidePos]->itemId();
    }
    for(j = 0; j < PICTURE_NUM; j++){
        itemList[j]->setPos(m_MidLine.pointAt(m_PointList[j]));
        itemList[j]->setZValue(m_ZValueList[j]);
        itemList[j]->setScale(m_PixmapScaleList[j]);
        itemList[j]->setTransformationMode(Qt::SmoothTransformation);
    }
}

void PictureSlideShow::rollNextItem()
{
    int id = currentMainSlideID;
    if(++id == PICTURE_NUM){
        id = 0;
    }
    buttongroup->button(id)->setChecked(true);
    rollItem(id);
}

void PictureSlideShow::rollPrevItem()
{
    int id = currentMainSlideID;
    if(--id < 0){
        id = PICTURE_NUM - 1;
    }
    buttongroup->button(id)->setChecked(true);
    rollItem(id);

}
