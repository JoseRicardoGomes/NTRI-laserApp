/***********************************************************
Universidade Lusiada de VN de Famalicão                    *
NTRI - tracking camera Proof Of Concept                    *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/
#ifndef PROCESSINGIMAGE_H
#define PROCESSINGIMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

class processingImage
{
public:
    processingImage();
    ~processingImage();
    void setHmin(int);
    void setHmax(int);
    void setSmin(int);
    void setSmax(int);
    void setVmin(int);
    void setVmax(int);
    void setHSV(int, int);
    void setPosxPosy(int, int);
    void setImg();
    void morph();
    void trackObject();
    void drawObject();

    Mat getImg();
    Mat getImgThreshold();
    vector<int> getHSV();

    //Height and width of the image for some calculations
    int imgWidth;
    int imgHeight;
    //Object coordinates -> center of object rectangle
    //Initializing is the center of the image
    int posX;
    int posY;
private:
    //H S V values from imageHSV
    int H_Min;
    int H_Max;
    int S_Min;
    int S_Max;
    int V_Min;
    int V_Max;
    //Tracking object function
    //Object not to be deleted
    int NonDeleteObject;
    //Variables to calculate the object closest to the last object
    double pointsDistance;
    Point Prect;
    //Variables to detect objects in image
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Rect> boundRect();
    //Camera capture
    VideoCapture *cap;
    //Images and images of processing
    Mat img;
    Mat imgHSV;
    Mat imgThreshold;
};

#endif // PROCESSINGIMAGE_H
