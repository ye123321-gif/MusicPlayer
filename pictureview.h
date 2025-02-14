#ifndef PICTUREVIEW_H
#define PICTUREVIEW_H

#include <QGraphicsView>

class pictureView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit pictureView(QWidget *parent = NULL);
    virtual ~pictureView();
protected:
    virtual void resizeEvent(QResizeEvent *event); //

signals:
    void sizeChanged(const QSize &);
};

#endif // PICTUREVIEW_H
