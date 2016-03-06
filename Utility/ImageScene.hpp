#ifndef _0_IMAGESCENE_HPP
#define _0_IMAGESCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPointer>
class ImageItem;
class BarChart;

class ImageScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QPointer<QGraphicsObject> top_ = nullptr ;
public:
    ImageScene();
    ~ImageScene();

    void setTopItem(QGraphicsObject *);
    ImageItem * addImage( const QImage   );
    BarChart * addBarChart( QColor,QList<qreal> );
};

#endif // IMAGESCENE_HPP
