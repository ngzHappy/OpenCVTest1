#ifndef _0_IMAGEVIEW_HPP
#define _0_IMAGEVIEW_HPP

#include <QGraphicsView>

class ImageScene;
class ImageItem;
class BarChart;

class ImageView : public QGraphicsView
{
    Q_OBJECT
private:
    bool isFirstShow_=false;
    ImageScene * const scene_=nullptr;
    using QGraphicsView::setScene ;
    typedef QGraphicsView P;
public:

    ImageView();
    ~ ImageView();

    BarChart * addBarChart(  QColor,QList<qreal>);
    ImageItem * addImage( QImage  );
protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // IMAGEVIEW_HPP
