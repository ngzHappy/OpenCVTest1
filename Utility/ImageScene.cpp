#include "ImageScene.hpp"
#include "ImageItem.hpp"
#include "BarChart.hpp"
#include <cstdlib>
#include <algorithm>

ImageScene::ImageScene() {
    setSceneRect(0,0,1024,1024);
}

ImageScene::~ImageScene() {

}

BarChart * ImageScene::addBarChart(QColor a__,QList<qreal> b__) {
    auto * _item_=new BarChart( 
        QColor(
        a__.red()/2+2,
        a__.green()/2+1,
        a__.blue()/2+3,
        std::min( a__.alpha()+100,255 )
        ) ,std::move(b__)
        );
    _item_->setPos( std::rand()&127,std::rand()&63 );
    addItem(_item_);
    return _item_;
}

ImageItem * ImageScene::addImage(const QImage image__) {
    auto * _item_=new ImageItem;
    _item_->setImage(image__);
    _item_->setPos( std::rand()&127,std::rand()&63 );
    addItem(_item_);
    return _item_;
}

void ImageScene::setTopItem(QGraphicsObject * item__) {

    if (item__==nullptr) { return; }
    QGraphicsObject * _obj_=top_.data();
    if (_obj_==item__) { return; }
    if (_obj_) { _obj_->setZValue(0.5); }
    item__->setZValue(1.0);
    top_=QPointer<QGraphicsObject>(item__);

}

/*
*/
