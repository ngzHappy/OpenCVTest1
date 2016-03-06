#ifndef _0_IMAGEITEM_HPP
#define _0_IMAGEITEM_HPP

#include <QGraphicsWidget>
#include <QImage>
#include <opencv2/opencv.hpp>

class ImageItem : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
private:
    QImage image_;
    QString title_;
public:

    static constexpr int toolBarHeight() { return 16; }

    ImageItem();
    ~ImageItem();

    const QImage & image()const {return image_;}
    void setImage( QImage );
    void setImage( cv::Mat );

    const QString & title()const{return title_;}
    void setTitle( QString );

signals:
    void imageChanged();
    void titleChanged();
public slots:
    void onClose() { _p_onClose(); }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;
private:
    void _p_onClose();
};

#endif // IMAGEITEM_HPP
