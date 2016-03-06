#include <QApplication>
#include <QTextCodec>
#include <QDir>
#include "Window.hpp"
#include <ImageItem.hpp>
#include <OpencvQtUtility.hpp>

int main(int argc,char *argv[]) {
    QApplication app(argc,argv);

    {
        QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",BUILD_PATH_"/../Images");
    }

    Window window;
    {
        QImage image_=QImage("images:000001");
        cv::Mat mat = qImage2OpencvMat( image_ );
        cv::Mat child_mat=mat(cv::Rect(100,100,200,200));
        cv::blur(child_mat,child_mat,{3,3});
        window.addImage( opencvMat2QImage(mat) )->setTitle("blur ROI");
        window.addImage( image_ )->setTitle("normal");
    }
    
    window.show();

    return app.exec();
}


