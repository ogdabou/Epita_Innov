#include "colordetector.h"

ColorDetector::ColorDetector()
{
}

ColorDetector::ColorDetector(cv::Scalar mincolor, cv::Scalar maxcolor)
{
    this->minColor = mincolor;
    this->maxColor = maxcolor;
}

cv::Mat ColorDetector::detect(cv::Mat inputFrame)
{
    cv::cvtColor(inputFrame, HSV, CV_BGR2HSV);
    cv::inRange(HSV, cv::Scalar(50,50,50), cv::Scalar(255,255,255),threshold);

    return threshold;
}
