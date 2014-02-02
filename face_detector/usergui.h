#ifndef USERGUI_H
#define USERGUI_H
#include "mainHeader.hpp"
#include "interestzone.h"

class UserGUI
{
public:
    UserGUI();
    cv::Mat print(cv::Mat frame, std::vector<InterestZone> &zone_interest);
};

#endif // USERGUI_H
