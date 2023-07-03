#ifndef PICTUREITEM_H
#define PICTUREITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPixmap>
class pictureItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit pictureItem(QGraphicsObject *parent = NULL);
    explicit pictureItem(const QPixmap &pixmap, QGraphicsItem *parent = NULL);
    virtual ~pictureItem();
    void setPixmap(const QPixmap &pixmap);
    QPixmap pixmap() const;
     virtual QRectF boundingRect() const;
    void setTransformationMode(Qt::TransformationMode mode);
    QPointF offset() const;
    void setOffset(const QPointF &offset);
    virtual int type()const;
    void setType(int type);
    int itemId()const;
    void setItemId(int id);
signals:
    void clicked();
    void clickedId(int);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:

private:
    QPointF pressedSceneP;
    QPointF m_offset;
    QPointF m_pos;
    Qt::TransformationMode mode;
    QPixmap m_pixmap;
    bool isPressed;
    int m_type;
    int m_id;
    qreal m_pointPercent;
};

#endif // PICTUREITEM_H
