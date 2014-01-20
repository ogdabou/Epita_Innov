#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include "mainHeader.hpp"
#include "interestzone.h"

class ColorDetector
{
    public:
        ColorDetector();
        ColorDetector(cv::Scalar mincolor, cv::Scalar maxcolor);
        cv::Mat detect(cv::Mat inputFrame,  std::vector<InterestZone>* list_inter_zone);

    private:
        cv::Mat HSV;
        cv::Mat threshold;
        cv::Scalar minColor;
        cv::Scalar maxColor;
};

#endif // COLORDETECTOR_H
