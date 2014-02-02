#ifndef MVT_DETECTION_H
#define MVT_DETECTION_H

#include "mainHeader.hpp"
#include "interestzone.h"

class Mvt_detection
{
public:
    Mvt_detection();
    ~Mvt_detection();
    cv::Mat start(cv::Mat frame, cv::Mat oldFrame,std::vector<InterestZone> list_inter_zone);
protected:
    cv::BackgroundSubtractorMOG2* bg;
};

#endif // MVT_DETECTION_H
