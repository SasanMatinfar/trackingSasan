#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QTimer* videoUpdateTimer;
    int currentFrame;

    //openCV setup, cleanup and processing
    void setUpOpenCV(void);
    void cleanUpOpenCv(void);
    Mat processFrame(Mat& frame);

    //Open cv variables
    VideoCapture* cap;
    double videoFps;


public slots:
    void videoTimer(void);
};

#endif // WIDGET_H
