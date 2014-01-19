#ifndef MVT_DETECTION_H
#define MVT_DETECTION_H

#include "mainHeader.hpp"

class Mvt_detection
{
public:
    Mvt_detection();
    ~Mvt_detection();
    cv::Mat start(cv::Mat frame);
protected:
};

#endif // MVT_DETECTION_H
