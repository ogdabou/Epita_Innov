#ifndef MYRECOGNIZER_HPP
#define MYRECOGNIZER_HPP

#include "mainHeader.hpp"

class MyRecognizer
{
    public:
        MyRecognizer();
        ~MyRecognizer();
        cv::Mat detect(cv::Mat frame,  std::vector<InterestZone> list_inter_zone);
        void setClassifier(cv::CascadeClassifier ccl);

    private:
        cv::CascadeClassifier classifier;
        cv::Rect copyRect(cv::Rect tocopy);

        const char* CASCADE_REF;
};

#endif // MYRECOGNIZER_HPP
