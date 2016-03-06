#include "MainWindow.hpp"
#include <ImageView.hpp>
#include <QHBoxLayout>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    image_view_=new ImageView;
    QHBoxLayout * _layout_=new QHBoxLayout;
    this->setLayout(_layout_);
    _layout_->setMargin(0);
    _layout_->setSpacing(0);
    _layout_->addWidget(image_view_);
    this->resize(666,666);
}

QGraphicsScene * MainWindow::getScene() const{
    return image_view_->scene() ;
}

ImageItem * MainWindow::addImage(QImage image__) {
    return image_view_->addImage(std::move(image__));
}

BarChart * MainWindow::addBarChart(QColor a__,QList<qreal> b__) {
    return image_view_->addBarChart(a__,std::move(b__));
}

MainWindow::~MainWindow() {

}

/*
*/
