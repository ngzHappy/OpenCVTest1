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
        QImage image1("images:000002"),image2("images:000003");
        window.addImage( image1 )->setTitle("src1");
        window.addImage( image2 )->setTitle("src2");
        cv::Mat mat1 = qImage2OpencvMat( image1 );
        cv::Mat mat2 = qImage2OpencvMat( image2 );
        cv::Mat ans;
        cv::addWeighted(mat1,0.3,mat2,0.7,0.0 ,ans);
        window.addImage( opencvMat2QImage(ans) )->setTitle("add_0");
        window.addImage( opencvMat2QImage( 0.7*mat1 + 0.3*mat2+cv::Scalar(0.1,0.2,0.3) ) )->setTitle("add_1");
    }
    window.show();

    return app.exec();
}


