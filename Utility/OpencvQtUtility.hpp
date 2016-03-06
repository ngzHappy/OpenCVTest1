#ifndef _0_OPENCVQTUTILITY_HPP
#define _0_OPENCVQTUTILITY_HPP

#include <opencv2/opencv.hpp>
#include <QImage>

inline QImage opencvMat2QImage( const cv::Mat & );
inline cv::Mat qImage2OpencvMat( const QImage & );


/*************************/
inline QImage opencvMat2QImage(const cv::Mat & image__){
    QImage ans_;
    if( image__.type() == CV_8UC3 ){
        ans_ = QImage(
                    image__.data,
                    image__.cols,
                    image__.rows,
                    image__.step,
                    QImage::Format::Format_RGB888 );
        return ans_.copy();
    }

    if( image__.type() == CV_8UC4 ){
        ans_ = QImage(
                    image__.data,
                    image__.cols,
                    image__.rows,
                    image__.step,
                    QImage::Format::Format_RGBA8888 );
        return ans_.copy();
    }

    if(image__.type() == CV_8UC1 ){
        ans_ = QImage(
                    image__.data,
                    image__.cols,
                    image__.rows,
                    image__.step,
                    QImage::Format::Format_Grayscale8 );
        return ans_.copy();
    }

    return ans_;
}

inline cv::Mat qImage2OpencvMat( const QImage & image__){
    const QImage image_ = image__.convertToFormat( QImage::Format::Format_RGB888 );
    cv::Mat ans (
                image_.height(),image_.width(),
                CV_8UC3, const_cast<uchar *>(image_.bits()),image_.bytesPerLine()
                );
    return ans.clone() ;
}

#endif // OPENCVQTUTILITY_HPP

