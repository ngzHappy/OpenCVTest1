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
        image_ = image_.convertToFormat( QImage::Format::Format_RGBA8888 );
        {
            cv::Mat mat=cv::Mat(
                        image_.height(),
                        image_.width(),
                        CV_8UC4,
                        const_cast<uchar *>(image_.bits()),
                        image_.bytesPerLine()
                        );
            std::vector< cv::Mat > rgba;
            cv::split(mat,rgba);
            cv::blur(rgba[0],rgba[0],{ 3,3 });
            cv::blur(rgba[1],rgba[1],{ 3,3 });
            //cv::blur(rgba[2],rgba[2],{ 3,3 });
            cv::merge(rgba,mat);
        }
        window.addImage( image_ )->setTitle("blur Red Green");
        window.addImage(QImage("images:000001"))->setTitle("common");
    }

    window.show();
    return app.exec();
}


