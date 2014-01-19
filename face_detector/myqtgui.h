#ifndef MYQTGUI_H
#define MYQTGUI_H

#pragma once
#include "mainHeader.hpp"
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

#include "interestzone.h"

class MyQtGui : public QWidget
{
    Q_OBJECT
public:
    explicit MyQtGui(QWidget *parent = 0) : QWidget(parent) {
        this->writing = false;
    }
    MyQtGui(QTimer* timer);

    QSize sizeHint() const { return _qimage.size(); }
    QSize minimumSizeHint() const { return _qimage.size(); }

public slots:
    void showImage();
    void setImage(cv::Mat image);

protected:
    void paintEvent(QPaintEvent* /*event*/) {
        // Display the image
        QPainter painter(this);
        painter.drawImage(QPoint(0,0), _qimage);
        painter.end();
    }

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    QImage _qimage;
    cv::Mat _tmp;
    cv::Mat currentImage;
    cv::Mat oldImage;

    cv::Mat tmpImage;
    cv::Scalar defaultZoneColor;

    QTimer* timer;

    std::vector<InterestZone> zoneList;

    InterestZone currentZone;

    cv::Point drawP1;
    cv::Point drawp2;

    bool writing;
    int rectX;
    int rectY;
};

#endif // MYQTGUI_H
