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
        cv::Mat mat = qImage2OpencvMat( QImage("images:000001") );
        cv::filter2D(mat,mat,mat.depth(),cv::Matx33f(0,-1,0,-1,5,-1,0,-1,0));
        window.addImage( opencvMat2QImage(mat) )->setTitle("filter2D");
    }
    window.addImage( QImage("images:000001") )->setTitle("normal");
    window.show();

    return app.exec();
}


