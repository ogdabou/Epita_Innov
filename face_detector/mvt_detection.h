#ifndef MVT_DETECTION_H
#define MVT_DETECTION_H

#include "mainHeader.hpp"

class Mvt_detection
{
public:
    Mvt_detection();
    ~Mvt_detection();
    void start(cv::Mat frame, const char *targetWindow);
protected:
};

#endif // MVT_DETECTION_H
