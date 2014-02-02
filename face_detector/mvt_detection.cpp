#include "mvt_detection.h"

std::vector<std::vector<cv::Point> > findmvt_in_contours(std::vector<InterestZone> &list_inter_zone, std::vector<std::vector<cv::Point> > contours);

Mvt_detection::Mvt_detection()
{
    bg = new cv::BackgroundSubtractorMOG2(10, 16, false);

}

Mvt_detection::~Mvt_detection()
{
}

cv::Mat Mvt_detection::start(cv::Mat frame, cv::Mat oldFrame, std::vector<InterestZone > &list_inter_zone)
{
    cv::Mat back;
    cv::Mat fore;
    cv::Mat tmp;
    frame.copyTo(tmp);
    std::vector<std::vector<cv::Point> > contours;

   bg->operator ()(oldFrame, fore);
   bg->getBackgroundImage(back);
   cv::erode(fore,fore,cv::Mat());
   cv::dilate(fore,fore,cv::Mat());
   cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

   cv::drawContours(tmp,contours,-1,cv::Scalar(0,0,255),2);
   std::vector<std::vector<cv::Point> > temp = this->findmvt_in_contours(&list_inter_zone, contours);
   cv::drawContours(tmp,temp, -1, cv::Scalar(255,0,0),2);

   return tmp;
}
std::vector<std::vector<cv::Point> > Mvt_detection::findmvt_in_contours(std::vector<InterestZone> *list_inter_zone, std::vector<std::vector<cv::Point> > contours) {
    std::vector<std::vector<cv::Point> > blue_point;
    for (std::vector<std::vector<cv::Point> >::iterator it = contours.begin(); it != contours.end() ; ++it){
        std::vector<cv::Point> blue_1;
        for (std::vector<cv::Point>::iterator it2 = (*it).begin(); it2 < (*it).end(); ++it2) {
            for(std::vector<InterestZone>::iterator it_z = list_inter_zone->begin() ;it_z < list_inter_zone->end() ; ++it_z) {
                if(((*it_z).p1.x < (*it2).x && (*it_z).p1.y < (*it2).y) &&
                   ((*it_z).p2.x > (*it2).x && (*it_z).p2.y > (*it2).y)) {

                    blue_1.push_back((*it2));
                    (*it_z).motion = TRUE;
                }
                else
                {
                    (*it_z).motion = FALSE;
                }
            }
        }
        blue_point.push_back(blue_1);
    }

    return blue_point;
}
