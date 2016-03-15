#include <QApplication>
#include <QTextCodec>
#include <QDir>
#include "Window.hpp"
#include <ImageItem.hpp>
#include <OpencvQtUtility.hpp>
#include <QGraphicsScene>

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
        QImage image_("images:000001");
        cv::Mat mat = qImage2OpencvMat( image_ );
        window.addImage( image_ )->setTitle( "normal" );
        const int dim = 256;
        cv::Mat lut( 1,&dim,CV_8U );
        for (int i=0; i<=255;++i) {
            lut.at<unsigned char>(i)=255-i;
        }
        cv::LUT(mat,lut,mat);
        window.addImage( opencvMat2QImage(mat) )->setTitle("lut");
    }

    window.show();

    return app.exec();
}


