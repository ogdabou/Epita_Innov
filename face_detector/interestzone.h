#ifndef INTERESTZONE_H
#define INTERESTZONE_H

#include "mainHeader.hpp"

class InterestZone
{
    public:
        InterestZone();
        InterestZone(cv::Point p1, cv::Point p2);
        cv::Point p1;
        cv::Point p2;
        void reset();
        bool motion;
};

#endif // INTERESTZONE_H
