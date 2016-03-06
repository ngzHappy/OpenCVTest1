#include "ImageItem.hpp"
#include "OpencvQtUtility.hpp"
#include "ImageScene.hpp"
#include <QPainter>
#include <cstdlib>

namespace {
class CloseButtonItem : public QGraphicsWidget {
    friend class ImageItem;
    ImageItem *  const super_;
public:
    CloseButtonItem(ImageItem * p):QGraphicsWidget(p),super_(p) {
        setToolTip(QString::fromUtf8(u8R"(关闭图片)"));
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *) override {
        super_->onClose();
    }
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget) {
        constexpr float _sp_=3.0f;
        constexpr float _width_=ImageItem::toolBarHeight()-_sp_;

        painter->setPen(QPen(QColor(200,56,67),2.2f));
        painter->drawLine(
                    QPointF{ _sp_,_sp_ },
                    QPointF{ _width_,_width_ }
                    );
        painter->drawLine(
                    QPointF{ _width_,_sp_ },
                    QPointF{ _sp_,_width_ }
                    );

        return; (void)widget; (void)option;
    }
};
}

void ImageItem::setTitle( QString title__){
    if(title_==title__){return;}
    title_=std::move(title__);
    update();
    titleChanged();
}

ImageItem::ImageItem() {
    setFlag(QGraphicsItem::ItemIsMovable);
    CloseButtonItem * close_=new CloseButtonItem(this);
    close_->resize(toolBarHeight(),toolBarHeight());
}

void ImageItem::_p_onClose() {
    QGraphicsScene * _sc_=scene();
    if (_sc_==nullptr) { this->deleteLater(); }
    _sc_->removeItem(this);
}

void ImageItem::setImage(QImage image__) {
    QSize _size_old_=image_.size();
    image_=std::move(image__);
    QSizeF _size_=image_.size();
    if (_size_!=_size_old_) {
        this->resize(QSizeF(_size_.width(),_size_.height()+toolBarHeight()));
    }
    else {
        update();
    }
    imageChanged();
}

void ImageItem::setImage(cv::Mat image__) {
    setImage(opencvMat2QImage(image__));
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
    QGraphicsScene * _sc_=scene();
    ImageScene * _scene_=qobject_cast<ImageScene *>(_sc_);
    if (_scene_) {
        _scene_->setTopItem(this);
    }
}

void ImageItem::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget) {

    {
        painter->setPen(QPen(QColor(63+(std::rand()&63),102,255,0),2));
        painter->setBrush(QColor(12,102,255,58));
        painter->drawRect(0,0,size().width(),ImageItem::toolBarHeight());
    }

    if(title_.isEmpty()==false)
    {
        painter->setPen( QPen(QColor(0,0,0,250),1) );
        painter->setBrush( QColor(0,0,0,250) );
        {
            auto _font_=painter->font();
            _font_.setPixelSize( toolBarHeight()-1 );
            painter->setFont(_font_);
        }
        painter->drawText(
            QRectF( toolBarHeight()*1,0 ,size().width(),toolBarHeight()),
            title_);
    }

    painter->drawImage(0,toolBarHeight(),image_);
    return; (void)widget; (void)option;
}

ImageItem::~ImageItem() {}
