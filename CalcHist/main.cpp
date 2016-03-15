#include <QApplication>
#include <QTextCodec>
#include <QDir>
#include "Window.hpp"
#include <BarChart.hpp>
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
        QImage image_("images:000002") ;
        window.addImage( image_ )->setTitle("normal");

        image_ = image_.convertToFormat( QImage::Format::Format_RGB888 );
        cv::Mat mat (
                    image_.height(),image_.width(),
                    CV_8UC3, const_cast<uchar *>(image_.bits()),
                    image_.bytesPerLine()
                    );

        std::vector< cv::Mat > rgb;
        cv::split(mat,rgb);

        class RGBData {public:
            QString name;
            QColor color;
            int index;
        };

        const static std::vector<RGBData > rgb_data{ 
            RGBData{"red",QColor(200,20,30,50),0},
            RGBData{"green",QColor(20,200,30,50),1},
            RGBData{"blue",QColor(20,20,200,50),2}
        };

        {
            for (const RGBData & i:rgb_data) {

                cv::MatND ans;
                cv::Mat mask;
                cv::calcHist(
                    std::vector<cv::Mat>{rgb[i.index]},
                    std::vector<int>{0},
                    mask,
                    ans,
                    std::vector<int>{256},
                    std::vector<float>{0.0f,255.0f}
                    );
                {
                    float * begin_=ans.ptr<float>();
                    float * end_=begin_+256;
                    QList<qreal> toDraw;
                    toDraw.reserve(256);
                    for (; begin_!=end_; ++begin_) { toDraw.push_back(*begin_); }
                    window.addBarChart(i.color,toDraw)->setTitle(i.name);
                }
            }
        }

    }

    window.show();

    return app.exec();
}


