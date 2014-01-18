#include "facedetectapp.h"

FaceDetectApp::FaceDetectApp()
{
    WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    CASCADE_REF = "haarcascade_frontalface_default.xml";
    WEBCAM_DETECT_WINDOW = "Face Detection";
    WEBCAM_MVT_WINDOW = "Movement detection";
    WAITING_TIME_IN_MS = 5;
}

FaceDetectApp::~FaceDetectApp()
{
    cv::destroyAllWindows();
}

int FaceDetectApp::start(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::cout << "time requested : "<< argv[1];
        WAITING_TIME_IN_MS = atoi(argv[1]);
    }

    capture.open(0);

    if (!capture.isOpened())
    {
        return -1;
    }
    else
    {
        qDebug() << "Sucess to access webcam!";
    }
    cv::namedWindow(WEBCAM_DETECT_WINDOW, 1);
    cv::namedWindow(WEBCAM_RAW_WINDOW_TITLE, 1);
    cv::namedWindow(WEBCAM_MVT_WINDOW,1);

    cv::Mat singleFrame;
    char pressedKey = 'l';

    classifier.load(CASCADE_REF);

    faceRecognizer.setClassifier(classifier);
    while(pressedKey != 'q' && pressedKey != 'Q')
    {
        capture >> singleFrame;
        if (!singleFrame.empty())
        {
            cv::imshow(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
            faceRecognizer.detectAndDisplay(singleFrame, WEBCAM_DETECT_WINDOW);
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
