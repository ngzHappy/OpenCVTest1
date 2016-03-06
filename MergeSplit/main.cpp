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
        QImage image("images:000001");
        cv::Mat mat = qImage2OpencvMat( image );
        std::vector< cv::Mat > rgb;
        cv::split(mat,rgb);
        if(rgb.size()>0) {
            window.addImage( opencvMat2QImage(rgb[0]) )->setTitle("r");
            rgb[0]*=1.5;
        }
        if(rgb.size()>1) {
            window.addImage( opencvMat2QImage(rgb[1]) )->setTitle("g");
        }
        if(rgb.size()>2) {
            window.addImage( opencvMat2QImage(rgb[2]) )->setTitle("b");
        }
        window.addImage( image )->setTitle("normal");
        cv::merge(rgb,mat);

        window.addImage( opencvMat2QImage(mat) )->setTitle("merge");
    }
    window.show();

    return app.exec();
}


