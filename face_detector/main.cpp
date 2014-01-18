#include <iostream>
#include <QDebug>


using namespace std;

#include "mainHeader.hpp"
#include "myrecognizer.hpp"

using namespace cv;

int main()
{
    const char* WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    const char* CASCADE_REF = "haarcascade_frontalface_default.xml";
    const int WEBCAM_CONNECTION_ATTEMPT = 5;

    cv::VideoCapture capture(0);

    if (!capture.isOpened())
    {
        return -1;
    }
    else
    {
        qDebug() << "Sucess to access webcam!";
    }
    namedWindow(WEBCAM_RAW_WINDOW_TITLE, 1);
    cv::Mat singleFrame;
    capture >> singleFrame;
    imshow(WEBCAM_RAW_WINDOW_TITLE, singleFrame);

    char pressedKey = 'l';
    while(pressedKey != 'q' && pressedKey != 'Q')
    {
        capture >> singleFrame;
        if (!singleFrame.empty())
        {
            qDebug() << "Frame is not empty";
            imshow(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
            CascadeClassifier classifier;
            classifier.load(CASCADE_REF);
            MyRecognizer reco;
            reco.setClassifier(classifier);
            reco.detectAndDisplay(singleFrame, WEBCAM_RAW_WINDOW_TITLE);

//            imshow(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
            pressedKey = waitKey(10);
        }
        else
        {
            return 0;
        }
    }
    destroyAllWindows();
    return 0;
}



int mainLol ()
{
    CvCapture* capture = NULL; // will read a video or a webCam
    const int WEBCAM_CONNECTION_ATTEMPT = 5;
    const char* WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    const char* CASCADE_REF = "haarcascade_frontalface_default.xml";

    // sometimes the webcam is not detected directly.
    int attempt = 0;
    while (capture == NULL || !capture && attempt < WEBCAM_CONNECTION_ATTEMPT)
    {
        qDebug() << "capturing webcam";
        capture = cvCreateCameraCapture(CV_CAP_ANY);
        attempt += 1;
    }
    if (!capture)
    {
        qDebug() << "Cannot open webcam video";
        return 1;
    }
    else
    {
        CascadeClassifier classifier;
        if (!classifier.load(CASCADE_REF))
        {
            qDebug() << "failed to load classifier with ";
            qDebug() <<  CASCADE_REF;
        }

        // Window creation + show webcam
        cvNamedWindow(WEBCAM_RAW_WINDOW_TITLE, CV_WINDOW_AUTOSIZE);
        IplImage* webCamImages;

        char key = 'l';
        while (key !='Q' && key !='q')
        {
            webCamImages = cvQueryFrame(capture);
            cvShowImage(WEBCAM_RAW_WINDOW_TITLE, webCamImages);
            key = cvWaitKey(10);
        }
    }

    // free the memory
    cvDestroyAllWindows();
    cvReleaseCapture(&capture);


    return 0;
}

