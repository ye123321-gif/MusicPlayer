#include "pictureitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
pictureItem::pictureItem(QGraphicsObject *parent)
    : QGraphicsObject(parent),
      mode(Qt::SmoothTransformation),
      isPressed(false),
      m_type(0),
      m_id(0),
      m_pointPercent(0.0)

{

}

pictureItem::pictureItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      mode(Qt::SmoothTransformation),
      isPressed(false),
      m_type(0)
{
     m_pixmap = pixmap;
}

pictureItem::~pictureItem()
{

}

void pictureItem::setPixmap(const QPixmap &pixmap)
{
    prepareGeometryChange();
    m_pixmap = pixmap;
    update();
}

QPixmap pictureItem::pixmap() const
{
    return m_pixmap;
}

QRectF pictureItem::boundingRect() const
{
    if(m_pixmap.isNull())
    {
        return QRectF();
    }
    else {
        return QRectF(m_offset, m_pixmap.size() / m_pixmap.devicePixelRatio());
    }
}

void pictureItem::setTransformationMode(Qt::TransformationMode mode)
{
    if (mode != this->mode)
    {
        this->mode = mode;
        update();
    }
}

QPointF pictureItem::offset() const
{
    return m_offset;
}

void pictureItem::setOffset(const QPointF &offset)
{
    m_offset = offset;
    this->pos();
    if (m_offset == offset)
        return;
    prepareGeometryChange();
    m_offset = offset;
    update();
}

int pictureItem::type() const
{
    return m_type;
}

void pictureItem::setType(int type)
{
    m_type = type;
}

int pictureItem::itemId() const
{
    return m_id;
}

void pictureItem::setItemId(int id)
{
    m_id = id;
}

void pictureItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     //Left mouse button only
    if(event->button() == Qt::LeftButton)
    {
        pressedSceneP = event->pos();
        isPressed = true;
    }
}

void pictureItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isPressed && boundingRect().contains(event->pos())
                && boundingRect().contains(pressedSceneP))
        {
            isPressed = false;
            emit clicked();
            emit clickedId(type());
        }
    }
}
//calling update will call paint
void pictureItem::paint(QPainter *painter,
          const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->setRenderHint(QPainter::SmoothPixmapTransform,
                           (this->mode == Qt::SmoothTransformation));

    painter->drawPixmap(m_offset, m_pixmap);
}

