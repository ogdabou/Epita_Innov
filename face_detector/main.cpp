#include <iostream>
#include <QDebug>


using namespace std;

#include "mainHeader.hpp"
#include "facedetectapp.h"

using namespace cv;

int main(int argc, char *argv[])
{
    FaceDetectApp myFaceDetector;
    return myFaceDetector.start(argc, argv);
}

