#include "contourdetector.h"

ContourDetector::ContourDetector()
{
}

cv::Mat ContourDetector::detect(cv::Mat inputFrame)
{
    int thresh = 100;


    cv::RNG rng(12345);

      /// Detect edges using canny
      cv::cvtColor( inputFrame, src_gray, CV_BGR2GRAY );
      cv::Canny( src_gray, canny_output, thresh, thresh*2, 3 );
      /// Find contours
      cv::findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

      /// Draw contours
      cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
      for( int i = 0; i< contours.size(); i++ )
         {
           cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           cv::drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
         }
      return drawing;
}
