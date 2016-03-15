#ifndef STYLEITEM_HPP
#define STYLEITEM_HPP

#include <QGraphicsWidget>

class StyleItem :public QGraphicsWidget
{
    Q_OBJECT
private:
    typedef QGraphicsWidget P;
public:
    StyleItem();
    ~StyleItem();

    void paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget ) ;

};

#endif // STYLEITEM_HPP
