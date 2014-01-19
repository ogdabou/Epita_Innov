#ifndef FACEDETECTAPP_H
#define FACEDETECTAPP_H

#include "mainHeader.hpp"
#include "myrecognizer.hpp"
#include "mvt_detection.h"

class FaceDetectApp
{
    public:
        FaceDetectApp();
        ~FaceDetectApp();
        int start(int argc, char *argv[]);

    private:
        const char* WEBCAM_RAW_WINDOW_TITLE;
        const char* WEBCAM_DETECT_WINDOW;
        const char* WEBCAM_MVT_WINDOW;

        int WAITING_TIME_IN_MS;
        cv::VideoCapture capture;
        cv::CascadeClassifier classifier;
        MyRecognizer faceRecognizer;
        Mvt_detection mvt_detect;

        void createWindows();
        void readParams(int argc, char* argv[]);
        int openWebcamStream();
        int mainLoop();
};

#endif // FACEDETECTAPP_H
