#ifndef FACEDETECTAPP_H
#define FACEDETECTAPP_H

#include "mainHeader.hpp"
#include "myrecognizer.hpp"
#include "mvt_detection.h"
#include "myqtgui.h"
#include "colordetector.h"

#include <QDialog>
#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QGridLayout>

class FaceDetectApp : QObject
{
    Q_OBJECT
    public:
        FaceDetectApp();
        ~FaceDetectApp();
        int start(int argc, char *argv[]);

    private:
        const char* WEBCAM_RAW_WINDOW_TITLE;
        const char* WEBCAM_DETECT_WINDOW;
        const char* WEBCAM_MVT_WINDOW;
        const char* WEBCAM_COLOR_WINDOW;
        const char* WEBCAM_CONTOUR_WINDOW;

        int WAITING_TIME_IN_MS;
        cv::VideoCapture capture;
        cv::CascadeClassifier classifier;
        MyRecognizer faceRecognizer;
        Mvt_detection mvt_detect;
        ColorDetector colorDetector;

        std::map<const char*, MyQtGui*> resultPrinter;

        void createWindows();
        void readParams(int argc, char* argv[]);
        void buildMenu(cv::Mat frame);
        int openWebcamStream();
        int mainLoop(int argc, char* argv[]);
        void buildCentralWidget();
        void printImage(const char* windowName, cv::Mat frame);

    public slots:
        void refreshFrame();
};

#endif // FACEDETECTAPP_H
