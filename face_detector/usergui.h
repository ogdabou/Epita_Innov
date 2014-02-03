#ifndef USERGUI_H
#define USERGUI_H
#include "mainHeader.hpp"
#include "interestzone.h"
#include "Websocketserver.h"

class UserGUI
{
public:
    UserGUI();
    cv::Mat print(cv::Mat frame, std::vector<InterestZone> &zone_interest, WebSocketServer* myServer);
};

#endif // USERGUI_H
