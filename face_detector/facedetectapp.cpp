#include "facedetectapp.h"

FaceDetectApp::FaceDetectApp()
{
    WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    WEBCAM_DETECT_WINDOW = "Face Detection";
    WEBCAM_MVT_WINDOW = "Movement detection";
    WAITING_TIME_IN_MS = 5;
}

FaceDetectApp::~FaceDetectApp()
{
    cv::destroyAllWindows();
}

void FaceDetectApp::createWindows()
{
    cv::namedWindow(WEBCAM_DETECT_WINDOW, 1);
    cv::namedWindow(WEBCAM_RAW_WINDOW_TITLE, 1);
    cv::namedWindow(WEBCAM_MVT_WINDOW,1);
}

void FaceDetectApp::readParams(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "time requested : "<< argv[1];
        WAITING_TIME_IN_MS = atoi(argv[1]);
    }
}

int FaceDetectApp::openWebcamStream()
{
    capture.open(0);

    if (!capture.isOpened())
    {
        return -1;
    }
    else
    {
        qDebug() << "Sucess to access webcam!";
    }
    return 0;
}

int FaceDetectApp::start(int argc, char* argv[])
{
    readParams(argc, argv);
    if (openWebcamStream() == -1) return -1;
    createWindows();
    return mainLoop();
}

int FaceDetectApp::mainLoop()
{
    cv::Mat singleFrame;
    char pressedKey = 'l';
    while(pressedKey != 'q' && pressedKey != 'Q')
    {
        capture >> singleFrame;
        if (!singleFrame.empty())
        {
            cv::imshow(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
            faceRecognizer.detectAndDisplay(singleFrame, WEBCAM_DETECT_WINDOW);
            mvt_detect.start(singleFrame, WEBCAM_MVT_WINDOW);
            pressedKey = cv::waitKey(WAITING_TIME_IN_MS);
        }
        else
        {
            return 0;
        }
    }
    cv::destroyAllWindows();
    return 0;
}
