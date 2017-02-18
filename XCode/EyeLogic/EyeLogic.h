/*
* Author: Dimitri Vasilev, Dominik Konecny
* File: EyeLogic.h
* Eye Tracking Library
* v0.5
*/

#ifndef EYELOGIC_H
#define EYELOGIC_H

//OPENCV
#ifdef __APPLE__
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#else
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#endif

//STD
#include <iostream>
#include <vector>
#include <math.h>
#include <unistd.h>


using namespace std;
using namespace cv;

Mat loadImageAtPath(string path);
Mat cameraCapture();

class Eye
{
public:
    Eye(string pathToClassifier, bool left);
    ~Eye();

    //Cuts Out Eye from half image
    //left is true if using the users left half
    //of their face when looking at them
    bool detectKeyFeatures(Mat input);

    bool getBlink();

private:
    CascadeClassifier detector;

    //technically right eye ---> ;)
    bool leftEye;

    Mat original;
    Mat filtered;
    Mat filtforIris;

    Point eyeCorner;
    Point eyeCenter;
    size_t eyeRadius;

    bool blink;

    void equalHist();

    //+ brightens the eye, -darkens
    void addLighting(int intensity);

    void binaryThresh();

    void binaryThreshForIris();

    void applyGaussian();

    bool findPupil();

    bool findEyeCorner();
};

class ImgFrame
{
public:
    ImgFrame(Point resolution);
    ~ImgFrame();

    

    bool insertFrame(Mat frame);
    Point getCursorXY();

    //0 = None, 1 = Left, 2 = Right, 3 = Both/No Eyes Detected
    int getBlink();

private:
    Point screenResolution;
    CascadeClassifier faceDetector;
    Eye leftEye, rightEye;
};

#endif