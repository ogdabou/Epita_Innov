

#include "facedetectapp.h"


FaceDetectApp::FaceDetectApp()
{
    WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    WEBCAM_DETECT_WINDOW = "Face Detection";
    WEBCAM_MVT_WINDOW = "Movement detection";
    WEBCAM_COLOR_WINDOW = "Color detection";
    WEBCAM_CONTOUR_WINDOW = "Contour detection";
    WAITING_TIME_IN_MS = 5;
}

FaceDetectApp::~FaceDetectApp()
{
    cv::destroyAllWindows();
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
    return mainLoop(argc, argv);
}

void FaceDetectApp::buildMenu(cv::Mat frame)
{
    cv::putText(frame, "[s] to save screenshot.", cvPoint(30,30),
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cvScalar(255,255,255), 1, CV_AA);
}

void FaceDetectApp::refreshFrame()
{
    cv::Mat singleFrame;
    capture >> singleFrame;
    if (!singleFrame.empty())
    {
        buildMenu(singleFrame);
        printImage(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
        printImage(WEBCAM_DETECT_WINDOW, faceRecognizer.detect(singleFrame));
        printImage(WEBCAM_MVT_WINDOW, mvt_detect.start(singleFrame));

        printImage(WEBCAM_COLOR_WINDOW, colorDetector.detect(singleFrame));


       printImage(WEBCAM_CONTOUR_WINDOW, contourDetector.detect(singleFrame));

          /// Show in a window
          //namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
          //imshow( "Contours", drawing );

    }
    else
    {
        qDebug() << "The frame is empty!";
    }
}

void FaceDetectApp::printImage(const char *windowName, cv::Mat frame)
{
    resultPrinter.find(windowName)->second->showImage(frame);
}

int FaceDetectApp::mainLoop(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_RAW_WINDOW_TITLE, new MyQtGui()));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_DETECT_WINDOW, new MyQtGui()));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_MVT_WINDOW, new MyQtGui()));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_COLOR_WINDOW, new MyQtGui()));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_CONTOUR_WINDOW, new MyQtGui()));

    QWidget* widget = new QWidget();
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(resultPrinter.find(WEBCAM_RAW_WINDOW_TITLE)->second, 0, 0);
    layout->addWidget(resultPrinter.find(WEBCAM_DETECT_WINDOW)->second, 0, 1);
    layout->addWidget(resultPrinter.find(WEBCAM_MVT_WINDOW)->second, 1, 0);
    layout->addWidget(resultPrinter.find(WEBCAM_COLOR_WINDOW)->second, 1, 1);
    layout->addWidget(resultPrinter.find(WEBCAM_CONTOUR_WINDOW)->second, 1, 2);

    widget->setLayout(layout);
    mainWindow.setCentralWidget(widget);
    mainWindow.show();

    QTimer *timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(refreshFrame()));
    timer->start(WAITING_TIME_IN_MS);
    return app.exec();
}


