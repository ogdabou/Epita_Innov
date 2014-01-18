#include <iostream>
#include <QDebug>


using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>


using namespace cv;


int main (int argc, char* argv[])
{
    CvCapture* capture = NULL; // will read a video or a webCam
    const int WEBCAM_CONNECTION_ATTEMPT = 5;
    const char* WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    const string CASCADE_REF = "haarcascade_frontalface_default.xml";

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
            qDebug() << "failed to load classifier with " << CASCADE_REF;
        }

        // Window creation + show webcam
        cvNamedWindow(WEBCAM_RAW_WINDOW_TITLE, CV_WINDOW_AUTOSIZE);
        IplImage* webCamImages;

        char key = 'l';
        while (key !='Q' && key !='q')
        {
            webCamImages = cvQueryFrame(capture);
            determinant
            cvShowImage(WEBCAM_RAW_WINDOW_TITLE, webCamImages);
            key = cvWaitKey(10);
        }
    }

    // free the memory
    cvDestroyAllWindows();
    cvReleaseCapture(&capture);


    return 0;
}

