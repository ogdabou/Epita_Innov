

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

        cv::Mat src; cv::Mat src_gray;
        int thresh = 100;
        int max_thresh = 255;


        cv::RNG rng(12345);
        cv::Mat canny_output;
          std::vector<std::vector<cv::Point> > contours;
          std::vector<cv::Vec4i> hierarchy;

          /// Detect edges using canny
          cv::cvtColor( singleFrame, src_gray, CV_BGR2GRAY );
          cv::Canny( src_gray, canny_output, thresh, thresh*2, 3 );
          /// Find contours
          cv::findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

          /// Draw contours
          cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
          for( int i = 0; i< contours.size(); i++ )
             {
               cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
               cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
             }
          printImage(WEBCAM_CONTOUR_WINDOW, drawing);

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


