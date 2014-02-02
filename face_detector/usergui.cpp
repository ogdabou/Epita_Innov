#include "usergui.h"

UserGUI::UserGUI()
{
}

cv::Mat UserGUI::print(cv::Mat frame, std::vector<InterestZone> &zone_interest, WebSocketServer *myServer)
{
    cv::Mat frameCopy = frame;
    for (int i = 0 ; i < zone_interest.size(); i++) {
        std::cout << zone_interest[i].motion;
        if( zone_interest[i].motion == TRUE ) {
            cv::rectangle(frameCopy, zone_interest[i].p1, zone_interest[i].p2, cv::Scalar(0, 0, 255), 2, 8, 0);
            myServer->sendMessage("Detected");
        }
        else {
        cv::rectangle(frameCopy, zone_interest[i].p1, zone_interest[i].p2, cv::Scalar(0, 255, 0), 2, 8, 0);
        }

    }
    return frameCopy;
}
