#ifndef OPENCVQTCONVERT_H
#define OPENCVQTCONVERT_H

#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>



QImage cvMatToQImage( const cv::Mat &inMat );
QPixmap cvMatToQPixmap( const cv::Mat &inMat );


#endif // OPENCVQTCONVERT_H
