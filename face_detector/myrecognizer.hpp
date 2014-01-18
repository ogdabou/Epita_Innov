#ifndef MYRECOGNIZER_HPP
#define MYRECOGNIZER_HPP

#include "mainHeader.hpp"

class MyRecognizer
{
    public:
        MyRecognizer();
        ~MyRecognizer();
        void detectAndDisplay(cv::Mat frame, const char* targetWindow);
        void setClassifier(cv::CascadeClassifier ccl);

    private:
        cv::CascadeClassifier classifier;
        cv::Rect copyRect(cv::Rect tocopy);
};

#endif // MYRECOGNIZER_HPP
