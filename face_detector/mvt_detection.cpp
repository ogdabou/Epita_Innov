    #include "mvt_detection.h"


Mvt_detection::Mvt_detection()
{

}

Mvt_detection::~Mvt_detection()
{
}

cv::Mat Mvt_detection::start(cv::Mat frame)
{
    cv::Mat back;
    cv::Mat fore;
    cv::BackgroundSubtractorMOG2 bg(5,3,true) ;
    cv::namedWindow("Background");
    std::vector<std::vector<cv::Point> > contours;

   bg.operator ()(frame,fore);
   bg.getBackgroundImage(back);
   cv::erode(fore,fore,cv::Mat());
   cv::dilate(fore,fore,cv::Mat());
   cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
   cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
   return frame;
   //cv::imshow("Background",back);

}
