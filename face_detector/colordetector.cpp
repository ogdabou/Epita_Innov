#include "colordetector.h"

ColorDetector::ColorDetector()
{
}

ColorDetector::ColorDetector(cv::Scalar mincolor, cv::Scalar maxcolor)
{
    this->minColor = mincolor;
    this->maxColor = maxcolor;
}

cv::Mat ColorDetector::detect(cv::Mat inputFrame, std::vector<InterestZone>* list_inter_zone)
{
    cv::Mat tmp;
    inputFrame.copyTo(tmp);
    cv::cvtColor(tmp, HSV, CV_BGR2HSV);
    cv::inRange(HSV, cv::Scalar(50,50,50), cv::Scalar(255,255,255),threshold);

    return threshold;
}
