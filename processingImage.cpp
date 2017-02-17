#include "processingImage.h"

processingImage::processingImage()
{
    cap = new VideoCapture();
    cap->open(0);
    cap->read(img);
    imgWidth = img.cols;
    imgHeight = img.rows;
    posX = 0;
    posY = 0;

    H_Min = 0;
    H_Max = 180;
    S_Min = 0;
    S_Max = 255;
    V_Min = 0;
    V_Max = 255;
}

processingImage::~processingImage()
{
    delete cap;
}

void processingImage::setPosxPosy(int x, int y){
    posX = x;
    posY = y;
}

void processingImage::setHSV(int x, int y){
    cv::Vec3b pixel = imgHSV.at<cv::Vec3b>(x, y);
    if((pixel[0]- 10) <= 0){
        H_Min = 0;
    } else {
        H_Min = pixel[0] - 10;
    }

    if((pixel[0]+ 10) >= 180){
        H_Max = 180;
    } else {
        H_Max = pixel[0] + 10;
    }

    if((pixel[1]-60) <= 0){
        S_Min = 0;
    } else {
        S_Min = pixel[1] - 60;
    }

    if((pixel[1]+60) >= 255){
        S_Max = 255;
    } else {
        S_Max = pixel[1] + 60;
    }

    //S_Min = 200;
    //V_Min = 25;

    //V_Min = pixel[2];
}

void processingImage::drawObject(){
    circle(img, Point(imgWidth/2,imgHeight/2),10,Scalar(0,255,0),3);
    circle(img, Point(posX,posY),10,Scalar(0,255,0),3);
}

Mat processingImage::getImg(){
    return img;
}

Mat processingImage::getImgThreshold(){
    return imgThreshold;
}

void processingImage::setImg(){
    cap->read(img);
    flip(img, img, 1);
    //cvtColor(img,img,CV_BGR2RGB);
    cvtColor(img,imgHSV,CV_BGR2HSV);
    inRange(imgHSV,Scalar(H_Min,S_Min,V_Min),Scalar(H_Max,S_Max,V_Max),imgThreshold);
}

void processingImage::morph(){
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

    erode(imgThreshold,imgThreshold,erodeElement);
    erode(imgThreshold,imgThreshold,erodeElement);


    dilate(imgThreshold,imgThreshold,dilateElement);
    dilate(imgThreshold,imgThreshold,dilateElement);

}

void processingImage::trackObject(){

     findContours(imgThreshold, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

     vector<Rect> boundRect(contours.size());

     for(int i = 0; i < contours.size(); i++ )
     {
         approxPolyDP(Mat(contours[i]), contours[i], 3, true);
         boundRect[i] = boundingRect( Mat(contours[i]) );
     }

     for(int i = 0; i < contours.size(); i++){
         Prect = Point(boundRect[i].x + (boundRect[i].width / 2), boundRect[i].y + (boundRect[i].height / 2));
         if(i==0){
             pointsDistance = norm(Prect-Point(posX,posY));
             NonDeleteObject = i;
         }

         if(norm(Prect-Point(posX,posY)) <= pointsDistance){
            NonDeleteObject = i;
            pointsDistance = norm(Prect-Point(posX,posY));
         }
     }

     if(contours.size() != 0){
         posX = boundRect[NonDeleteObject].x + (boundRect[NonDeleteObject].width / 2);
         posY = boundRect[NonDeleteObject].y + (boundRect[NonDeleteObject].height / 2);

         rectangle(img,boundRect[NonDeleteObject].tl(),boundRect[NonDeleteObject].br(),Scalar(0,255,0),2,8,0);
         drawMarker(img,boundRect[NonDeleteObject].tl(),Scalar(0,255,0),MARKER_CROSS,20,3,8);
         drawMarker(img,boundRect[NonDeleteObject].br(),Scalar(255,0,0),MARKER_CROSS,20,3,8);
         drawMarker(img,Point(posX,posY),Scalar(0,0,255),MARKER_CROSS,20,3,8);
     }
}

void processingImage::setHmax(int value){
    H_Max = value;
}

void processingImage::setHmin(int value){
    H_Min = value;
}

void processingImage::setSmax(int value){
    S_Max = value;
}

void processingImage::setSmin(int value){
    S_Min = value;
}
void processingImage::setVmax(int value){
    V_Max = value;
}

void processingImage::setVmin(int value){
    V_Min = value;
}

vector<int> processingImage::getHSV(){
    vector<int> vectorTemp(6);
    vectorTemp[0] = H_Min;
    vectorTemp[1] = H_Max;
    vectorTemp[2] = S_Min;
    vectorTemp[3] = S_Max;
    vectorTemp[4] = V_Min;
    vectorTemp[5] = V_Max;
    return vectorTemp;
}
