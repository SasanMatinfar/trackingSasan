#include <stdio.h>
#include <iostream>
#include <cstring>
#include "widget.h"
#include "ui_widget.h"
#include "opencvqtconvert.h"
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <opencv2/core/utility.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <opencv2/core/cvstd.hpp>




using namespace cv;
using namespace std;



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    videoUpdateTimer(new QTimer()),
    currentFrame(0)
{
    ui->setupUi(this);


    // setup opencv
    setUpOpenCV();


    //setup video Update Timer
    videoUpdateTimer->setInterval(1000.f / videoFps);

    videoUpdateTimer->connect(videoUpdateTimer, SIGNAL(timeout()), this, SLOT(videoTimer()));

    videoUpdateTimer->start();

    update();
}


Widget::~Widget()
{
   //cleanup opencv
    cleanUpOpenCv();
    delete ui;
}



void Widget::setUpOpenCV(void)
{
    string videoFilename = "C:/Users/Sasan/Documents/Visual Studio 2015/Projects/TrackTwoPoints/raw_video.mp4";

    //prepare all your opencv objects here
    cap = new VideoCapture(videoFilename);

    if (!cap->isOpened()) {
          cout << "Error!" << endl; cout << "Can not open the file" << videoFilename << endl;
          return;
        }

    //cap->set(CV_CAP_PROP_POS_MSEC, 300);
    videoFps = cap->get(CV_CAP_PROP_FPS);
    cout << "Frame per seconds is: " << videoFps << endl;
}

void Widget::cleanUpOpenCv(void)
{
    // clean up open
    delete cap;
}

void Widget::videoTimer( void )
{
    std::cerr << "begin";
    std::cout << "Showing frame #" << currentFrame << std::endl;

    // here happens the OpenCV magic :D

    Mat frame;//(480, 640, CV_8U3);
    Mat frameRechts = frame; //processFrame(frame);

    bool succsess = this->cap->read(frame);


    if (!succsess) {
        cout << "Can not read the frame from the videofile, stopped videoupdatetimer" << endl;
        videoUpdateTimer->stop();
        return;
    }



    //convert and display the opencv image Links
    Mat frameSmallLinks;
    double resizeFactor = min((double)(ui->labelVideoLinks->width())/frame.cols, (double)(ui->labelVideoLinks->height()) /frame.rows);
    std::cerr << frame.rows << " " << frame.cols << '\n';
    std::cerr << resizeFactor << '\n';
    std::cerr << frame.empty() << '\n';
    std::cerr << int(frame.data) << '\n';
    cv::resize(frame, frameSmallLinks, cv::Size(frame.cols * resizeFactor, frame.rows * resizeFactor));
    QPixmap neuesFrameLinks = cvMatToQPixmap(frameSmallLinks);
    ui->labelVideoLinks->setPixmap(neuesFrameLinks);

    //display the opencv image Rechts
    Mat frameSmallRechts;
    std::cerr << frameRechts.rows << " " << frameRechts.cols << '\n';
    std::cerr << resizeFactor << '\n';
    std::cerr << frameRechts.empty() << '\n';
    std::cerr << int(frameRechts.data) << '\n';
    //cv::resize(frameRechts, frameSmallRechts, cv::Size(0,0), resizeFactor, resizeFactor);
    cv::resize(frame /* FIXME */, frameSmallRechts, cv::Size(0,0), resizeFactor, resizeFactor);
    QPixmap neuesFrameRechts = cvMatToQPixmap(frameSmallRechts);
    ui->labelVideoRechts->setPixmap(neuesFrameRechts);


    currentFrame++;
    std::cerr << "leaving";
}

Mat Widget::processFrame(Mat& frame)
{
    //dummy implementierung
    //!!!!!!
    //http://docs.opencv.org/3.1.0/d2/d0a/tutorial_introduction_to_tracker.html#gsc.tab=0





      // declares all required variables
      Rect2d roi = Rect2d();
      Mat frameT;
      // create a tracker object
      //Ptr<Tracker>* tracker = Tracker::create( "KCF" );
      // set input video
      std::string video = "C:/Users/Sasan/Documents/Visual Studio 2015/Projects/TrackTwoPoints/raw_video.mp4";
      VideoCapture cap(video);
      // get bounding box
      cap >> frameT;
      //roi=selectROI("tracker",frameT);
      //quit if ROI was not selected
      //if(roi.width==0 || roi.height==0)
       // return 0;
      // initialize the tracker
      //tracker->init(frameT,roi);
      // perform the tracking process
      printf("Start the tracking process, press ESC to quit.\n");
      for ( ;; ){
        // get frame from the video
        cap >> frameT;
        // stop the program if no more images
        if(frameT.rows==0 || frameT.cols==0)
          break;
        // update the tracking result
        //tracker->update(frameT,roi);
        // draw the tracked object
        rectangle( frameT, roi, Scalar( 255, 0, 0 ), 2, 1 );
        // show image with the tracked object
        //imshow("tracker",frameT);

      }



    return frameT;

}
