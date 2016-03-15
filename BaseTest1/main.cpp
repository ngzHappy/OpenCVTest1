#include <QApplication>
#include <QTextCodec>
#include <QDir>
#include "Window.hpp"
#include "StyleItem.hpp"
#include <ImageItem.hpp>
#include <OpencvQtUtility.hpp>
#include <QGraphicsScene>
#include <QStyle>
#include <QPalette>

int main(int argc,char *argv[]) {
    QApplication app(argc,argv);
    app.setStyleSheet("StyleItem{background:yellow}");

    {
        QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",BUILD_PATH_"/../Images");
    }

    Window window;
    {
        cv::Mat mat = qImage2OpencvMat( QImage("images:000001") );
        cv::blur(mat,mat,{3,3});
        window.addImage( opencvMat2QImage(mat) )->setTitle("blur");
    }

    {
        StyleItem * item = new StyleItem;
        //QPalette p = item->palette();
        //p.setBrush(QPalette::ColorRole::Background,QColor(255,0,0));
        //item->setPalette(p);
        window.getScene()->addItem(item);
    }

    window.addImage( QImage("images:000001") )->setTitle("normal");
    window.show();

    return app.exec();
}


