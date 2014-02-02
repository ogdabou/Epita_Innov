

#include "facedetectapp.h"


FaceDetectApp::FaceDetectApp()
{
    WEBCAM_RAW_WINDOW_TITLE = "Webcam Raw Video";
    WEBCAM_DETECT_WINDOW = "Face Detection";
    WEBCAM_MVT_WINDOW = "Movement detection";
    WEBCAM_COLOR_WINDOW = "Color detection";
    WEBCAM_CONTOUR_WINDOW = "Contour detection";
    WAITING_TIME_IN_MS = 5;
    list_inter_zone = new std::vector<InterestZone>;
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

void FaceDetectApp::buildMenuBar()
{
    menuBar = new QMenuBar();
    QMenu* fileMenu = menuBar->addMenu("File");

    QAction* takeScreenShot = new QAction("save screenshot", fileMenu);
    connect(takeScreenShot, SIGNAL(triggered()), this, SLOT(saveScreenShot()));
    fileMenu->addAction(takeScreenShot);
    mainWindow->setMenuBar(menuBar);
}

void FaceDetectApp::saveScreenShot()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString dateString = date.toString();
    QString timeString = time.toString();
    qDebug() << "Saving a screenshot";
    dateString.replace(" ", "_");
    timeString.replace(" ", "_");

    if(!QDir("screens/" + dateString).exists())
    {
        qDebug() << "creating screen folder for date " << dateString;
        QDir().mkdir("screens/" + dateString);
    }

    std::string fileName;
    fileName.append("screens/").append(dateString.toStdString()).append("/photo_").append(dateString.toStdString()).append(timeString.toStdString()).append(".jpg");

    if(cv::imwrite(fileName, currentFrame))
    {
        QMessageBox msgBox;
        msgBox.setText("Screeshot correctly saved");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Failed to save screenshot, verify that the folder 'screens' exists.");
        msgBox.exec();
    }
}

void FaceDetectApp::refreshFrame()
{
    cv::Mat singleFrame;
    capture >> singleFrame;
    if(oldFrame.empty())
    {
        singleFrame.copyTo(oldFrame);
    }

    singleFrame.size;
    //cv::Mat tmp;
    //cv::Size size(desktop->width() / 5, desktop->height() / 5);
    //cv::resize(singleFrame, tmp, size, 0, 0, cv::INTER_CUBIC);
    //tmp.copyTo(singleFrame);
    singleFrame.copyTo(currentFrame);
    MyQtGui* temp = resultPrinter.find(WEBCAM_DETECT_WINDOW)->second;
   /** std::vector<> zone_list;// = new std::vector<cv::Point>();
    for (int i = 0 ; i < temp->getZoneList().size(); i++) {
        InterestZone t = temp->getZoneList()[i];
        std::vector<cv::Point> point_list;
        point_list.push_back(t.p1);
        point_list.push_back(t.p2);
        zone_list.push_back(point_list);
    }*/


    if (!singleFrame.empty())
    {
        //buildMenu(singleFrame);
        printImage(WEBCAM_RAW_WINDOW_TITLE, singleFrame);
        printImage(WEBCAM_DETECT_WINDOW, faceRecognizer.detect(singleFrame, list_inter_zone));
        printImage(WEBCAM_COLOR_WINDOW, colorDetector.detect(singleFrame, list_inter_zone));
        printImage(WEBCAM_CONTOUR_WINDOW, contourDetector.detect(singleFrame, list_inter_zone));
        printImage(WEBCAM_MVT_WINDOW, mvt_detect.start(singleFrame, oldFrame, temp->getZoneList()));
    }
    else
    {
        qDebug() << "The frame is empty!";
    }
    singleFrame.copyTo(oldFrame);
}

void FaceDetectApp::printImage(const char *windowName, cv::Mat frame)
{
    resultPrinter[windowName]->setImage(frame);
    resultPrinter[windowName]->showImage();
}

int FaceDetectApp::mainLoop(int argc, char* argv[])
{
    QApplication app(argc, argv);
    desktop = QApplication::desktop();
    myClient = new Client();
    //myClient->setFixedSize(desktop->width() / 3, desktop->height() / 3);
    mainWindow = new QMainWindow();
    timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(refreshFrame()));
    buildMenuBar();

    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_RAW_WINDOW_TITLE, new MyQtGui(timer)));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_DETECT_WINDOW, new MyQtGui(timer)));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_MVT_WINDOW, new MyQtGui(timer)));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_COLOR_WINDOW, new MyQtGui(timer)));
    resultPrinter.insert(std::pair<const char*, MyQtGui*>(WEBCAM_CONTOUR_WINDOW, new MyQtGui(timer)));

    widget = new QWidget();
    layout = new QGridLayout();

    layout->addWidget(resultPrinter[WEBCAM_RAW_WINDOW_TITLE], 0, 0);
    layout->addWidget(resultPrinter[WEBCAM_DETECT_WINDOW], 0, 1);
    layout->addWidget(resultPrinter[WEBCAM_MVT_WINDOW], 1, 0);
    layout->addWidget(resultPrinter[WEBCAM_COLOR_WINDOW], 1, 1);
    layout->addWidget(resultPrinter[WEBCAM_CONTOUR_WINDOW], 1, 2);
    layout->addWidget(myClient, 0, 2);

    widget->setLayout(layout);
    mainWindow->setCentralWidget(widget);
    mainWindow->show();

    timer->start(WAITING_TIME_IN_MS);
    myServer = new WebSocketServer(8082, QtWebsocket::Tcp);
//    client.show();
    return app.exec();
}


