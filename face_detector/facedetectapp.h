#ifndef FACEDETECTAPP_H
#define FACEDETECTAPP_H

#include "mainHeader.hpp"
#include "myrecognizer.hpp"

class FaceDetectApp
{
    public:
        FaceDetectApp();
        ~FaceDetectApp();
        int start(int argc, char *argv[]);

    private:
        const char* WEBCAM_RAW_WINDOW_TITLE;
        const char* CASCADE_REF;
        const char* WEBCAM_DETECT_WINDOW;

        int WAITING_TIME_IN_MS;
        cv::VideoCapture capture;
        cv::CascadeClassifier classifier;
        MyRecognizer faceRecognizer;
};

#endif // FACEDETECTAPP_H
