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
        window.addImage( image_ )->setTitle("normal");
        std::vector<cv::Mat> rgb;
        std::vector<cv::Mat> rgb_ans{cv::Mat(),cv::Mat(),cv::Mat()};
        cv::split(mat,rgb);
        cv::equalizeHist(rgb[0],rgb_ans[0]);
        cv::equalizeHist(rgb[1],rgb_ans[1]);
        cv::equalizeHist(rgb[2],rgb_ans[2]);
        cv::merge(rgb_ans,mat);
        window.addImage( opencvMat2QImage(mat) )->setTitle("equalizeHist");
    }

    window.show();

    return app.exec();
}


