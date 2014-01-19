#include "interestzone.h"

InterestZone::InterestZone()
{

}

InterestZone::InterestZone(cv::Point p1, cv::Point p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

void InterestZone::reset()
{
    p1.x = 0;
    p2.x = 0;
    p1.y = 0;
    p2.y = 0;
}
