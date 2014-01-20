#ifndef CONTOURDETECTOR_H
#define CONTOURDETECTOR_H

#include "mainHeader.hpp"
#include "interestzone.h"

class ContourDetector
{
    public:
        ContourDetector();
        cv::Mat detect(cv::Mat inputFrame,  std::vector<InterestZone>* list_inter_zone);

    private:
        cv::Mat canny_output;
        cv::Mat src_gray;
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
};

#endif // CONTOURDETECTOR_H
