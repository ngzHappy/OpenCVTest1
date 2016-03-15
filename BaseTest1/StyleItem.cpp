#include "StyleItem.hpp"
#include <QStyleOptionGraphicsItem>
#include <QPainter>

StyleItem::StyleItem(){
    this->resize( 512,512 );
}

StyleItem::~StyleItem(){

}

void StyleItem::paint(
    QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget) {

    QPalette pattle_ = palette();
    painter->setBrush( pattle_.brush( QPalette::Background ) );
    painter->drawRect( boundingRect() );
    
   
    
}

