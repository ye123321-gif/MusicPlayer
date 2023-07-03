#ifndef PICTURESLIDESHOW_H
#define PICTURESLIDESHOW_H

#include <QWidget>
#include <QButtonGroup>
#include <QGraphicsView>
namespace Ui {
class PictureSlideShow;
}
class PictureSlideShow : public QWidget
{
    Q_OBJECT
public:
    PictureSlideShow(QWidget *parent = 0);
    void setButtonGroup();
    void setSlides();

    void setInitList();
    void PictureButtonAndPictureItemConnections();
    ~PictureSlideShow();
public slots:
    void rollItem(int id);
    void rollNextItem();
    void rollPrevItem();
private:
    Ui::PictureSlideShow *ui;
    QButtonGroup *buttongroup;
    QGraphicsScene *m_scene;
    QList<QPixmap> m_PixmapList;

    QLineF m_MidLine; //Middleline，to ensure slides locations
    QList<qreal> m_PointList; //x,y for each slides
    QList<qreal> m_ZValueList; //Priority of each slides
    QList<qreal> m_PixmapScaleList;//ratio of each slides to the graphview size
    int currentMainSlideID;
};

#endif // PICTURESLIDESHOW_H
