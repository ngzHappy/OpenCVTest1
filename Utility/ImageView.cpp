#include "ImageView.hpp"
#include "ImageScene.hpp"
#include <QScrollBar>
#include <memory>
#include <algorithm>

ImageView::ImageView() {
    const_cast<ImageScene * &>(scene_)=new ImageScene();
    {
        auto * old_=scene();
        setScene(scene_);
        delete old_;
    }
    this->setMinimumWidth(512);
    this->setMinimumHeight(512);
    scene_->setBackgroundBrush( QColor(200-30,200-15,200-10) );
}

BarChart * ImageView::addBarChart(QColor a__,QList<qreal> b__) {
    return scene_->addBarChart(a__,std::move(b__));
}

ImageItem * ImageView::addImage(QImage image__) {
    return scene_->addImage(std::move(image__));
}

void ImageView::resizeEvent(QResizeEvent *event){
    P::resizeEvent(event);
    {
        const QRectF _rect_=scene_->sceneRect();
        const QRectF _trect_=rect();
        const auto width_=std::max(_rect_.width(),_trect_.width())-0.5f;
        const auto height_=std::max(_rect_.height(),_trect_.height())-0.5f;
        scene_->setSceneRect(0,0,width_>1?width_:1,height_>1?height_:1);
    }
}

void ImageView::showEvent(QShowEvent *event){
    P::showEvent(event);
    if(false==isFirstShow_){
        isFirstShow_=true;
        this->verticalScrollBar()->setValue(0);
        this->horizontalScrollBar()->setValue(0);
    }
}

ImageView::~ImageView() {
    delete scene_;
}



