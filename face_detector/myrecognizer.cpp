#include "myrecognizer.hpp"

MyRecognizer::MyRecognizer()
{
}

MyRecognizer::~MyRecognizer()
{
}

void MyRecognizer::setClassifier(cv::CascadeClassifier ccl)
{
    this->classifier = ccl;
}

cv::Rect MyRecognizer::copyRect(cv::Rect tocopy)
{
    cv::Rect copy;
    copy.x = tocopy.x;
    copy.y = tocopy.y;
    copy.width = tocopy.width;
    copy.height = tocopy.height;
    return copy;
}

void MyRecognizer::detectAndDisplay(cv::Mat frame, const char *targetWindow)
{
    std::vector<cv::Rect> detected_faces;
    cv::Mat frameCopy;
    frame.copyTo(frameCopy);
    // To improve speed, change the min detection size
    classifier.detectMultiScale(frameCopy, detected_faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    for (int i = 0; i < detected_faces.size(); i++)
    {
        cv::Rect currentRegion = detected_faces.at(i);
        // Defining the regions of interest
        cv::Rect regionOne = copyRect(currentRegion);
        int currentArea = regionOne.width + regionOne.height;

        cv::Point p1(regionOne.x, regionOne.y);
        cv::Point p2(regionOne.x + regionOne.height, regionOne.y + regionOne.height);
        cv::rectangle(frameCopy, p1, p2, cv::Scalar(0, 255, 0), 2, 8, 0);

        cv::imshow(targetWindow, frameCopy);
    }
}
