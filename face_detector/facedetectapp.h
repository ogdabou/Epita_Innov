#ifndef FACEDETECTAPP_H
#define FACEDETECTAPP_H

#include "mainHeader.hpp"
#include "myrecognizer.hpp"
#include "mvt_detection.h"
#include "myqtgui.h"
#include "colordetector.h"
#include "contourdetector.h"
#include "Websocketserver.h"
#include "Client.h"

#include <QDialog>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QTimer>
#include <QGridLayout>
#include <algorithm>
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDir>
#include <string>

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
        ContourDetector contourDetector;
        cv::Mat currentFrame;
        cv::Mat oldFrame;
        std::map<const char*, MyQtGui*> resultPrinter;
        WebSocketServer* myServer;
        Client* myClient;

        QWidget* widget;
        QGridLayout* layout;
        QMenuBar* menuBar;
        QMainWindow* mainWindow;
        QDesktopWidget* desktop;
        QTimer *timer;

        void createWindows();
        void readParams(int argc, char* argv[]);
        void buildMenuBar();
        int openWebcamStream();
        int mainLoop(int argc, char* argv[]);
        void buildCentralWidget();
        void printImage(const char* windowName, cv::Mat frame);
        void buildMyQtGuis(const char *windowTitle);

    public slots:
        void refreshFrame();
        void saveScreenShot();
};

#endif // FACEDETECTAPP_H
