    #include "mvt_detection.h"


Mvt_detection::Mvt_detection()
{
    bg = new cv::BackgroundSubtractorMOG2(10, 16, false);
}

Mvt_detection::~Mvt_detection()
{
}

cv::Mat Mvt_detection::start(cv::Mat frame, cv::Mat oldFrame)
{
    cv::Mat back;
    cv::Mat fore;
    cv::Mat tmp;
    frame.copyTo(tmp);
    cv::namedWindow("Background");
    std::vector<std::vector<cv::Point> > contours;

   bg->operator ()(oldFrame, fore);
   bg->getBackgroundImage(back);
   cv::erode(fore,fore,cv::Mat());
   cv::dilate(fore,fore,cv::Mat());
   cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
   cv::drawContours(tmp,contours,-1,cv::Scalar(0,0,255),2);
   return tmp;
   //cv::imshow("Background",back);

}
