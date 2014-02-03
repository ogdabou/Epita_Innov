#include "myqtgui.h"

void MyQtGui::showImage()
{
    // Convert the image to the RGB888 format
    switch (currentImage.type()) {
    case CV_8UC1:
        cvtColor(currentImage, _tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cvtColor(currentImage, _tmp, CV_BGR2RGB);
        break;
    }


    assert(_tmp.isContinuous());
    _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);

    this->setFixedSize(currentImage.cols, currentImage.rows);


    std::string message;
    std::stringstream sstm;
    sstm << zoneList.size() << " interest zone";
    message = sstm.str();
    cv::putText(currentImage, message, cvPoint(30, 40),
        cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cvScalar(255,255,255), 1, CV_AA);
    for (unsigned int i = 0; i < zoneList.size(); i ++)
    {
        InterestZone zone = zoneList.at(i);
        cv::rectangle(currentImage, zone.p1, zone.p2, defaultZoneColor, 2, 8, 0);
    }
    if (currentZone.p2.x != 0 || currentZone.p2.y != 0)
    {
        cv::rectangle(currentImage, currentZone.p1, currentZone.p2, defaultZoneColor, 2, 8, 0);
    }

    repaint();
}

void MyQtGui::setImage(cv::Mat image)
{
    this->currentImage = image;
    defaultZoneColor = cv::Scalar(255, 0, 0);
}

MyQtGui::MyQtGui(const int width, const int height)
{
    //this->setFixedSize(width / 8, height / 8);
}

void MyQtGui::mouseMoveEvent(QMouseEvent *event)
{
    if (writing)
    {
        currentZone.p2.x = event->pos().x();
        currentZone.p2.y = event->pos().y();
        this->showImage();
    }
}

void MyQtGui::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        writing = true;
        currentZone.p1.x = event->pos().x();
        currentZone.p1.y = event->pos().y();
        currentImage.copyTo(oldImage);
    }
}

void MyQtGui::mouseReleaseEvent(QMouseEvent *event)
{
    writing = false;
    zoneList.push_back(currentZone);
    currentZone.reset();
}

MyQtGui::MyQtGui(QTimer *timer)
{
    this->timer = timer;
}

std::vector<InterestZone> MyQtGui::getZoneList()
{
    return zoneList;
}

void MyQtGui::setZoneList(std::vector<InterestZone> &value)
{
    zoneList = value;
}
