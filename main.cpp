/***********************************************************
Universidade Lusiada de VN de Famalicão                    *
NTRI - tracking camera Proof Of Concept                    *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/

#include "processingImage.cpp"
#include "GPIO.h"
#include "GPIO.cpp"
#include <wiringPi.h>

using namespace std;
using namespace cv;

processingImage procImg;
GPIO gpio;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN ){
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        procImg.setHSV(x, y);
        procImg.setPosxPosy(x, y);

    }
}

void YfollowFunc(int objy, int imgHeight){
		if(objy < imgHeight/2){
		//execute the down routine
		gpio.sequenceL(gpio.CameraA1,gpio.CameraA2,gpio.CameraB1,gpio.CameraB2);
	}
	if(objy > imgHeight/2){
		//execute the up routine
		gpio.sequenceR(gpio.CameraA1,gpio.CameraA2,gpio.CameraB1,gpio.CameraB2);
	}
	else{
		cout<< "Target Y located ready to deploy."<<endl;
	}
}

void XfollowFunc(int objx, int imgWidth){
	if(objx < imgWidth/2){
		//execute the left routine
		gpio.sequenceL(gpio.BaseA1,gpio.BaseA2,gpio.BaseB1,gpio.BaseB2);
	}
	else if(objx > imgWidth/2){
		//execute the right routine
		gpio.sequenceR(gpio.BaseA1,gpio.BaseA2,gpio.BaseB1,gpio.BaseB2);
	}
	else{
		cout<< "Target X located ready to deploy."<<endl;
	}
}

int main(void)
{

int objx;
int objy;
int imgHeight = procImg.imgHeight;
int imgWidth = procImg.imgWidth;

wiringPiSetup();

//gpio pinout mode setting
gpio.setGPIOpinModeBase(gpio.BaseA1, gpio.BaseA2, gpio.BaseB1, gpio.BaseB2);
gpio.setGPIOpinModeCamera(gpio.CameraA1, gpio.CameraA2, gpio.CameraB1, gpio.CameraB2);

//Create a window
namedWindow("ImageDisplay", CV_WINDOW_AUTOSIZE);
namedWindow("ImageThreshold", CV_WINDOW_AUTOSIZE);

//set the callback function for any mouse event
setMouseCallback("ImageDisplay", CallBackFunc, NULL);

	//show the image
    // Wait until user press some key
    while(true){
    	procImg.setImg();
     	procImg.morph();
    	procImg.trackObject();
    	procImg.drawObject();
	
    	//imgThreshold = procImg.getImgThreshold();

    	objx = procImg.posX;
	objy = procImg.posY;

    	imshow("ImageDisplay", procImg.getImg());

    	//we not show this on the pi.
    	//imshow("ImageThreshold", imgThreshold);

	 //Follow functions calls
	//for future scalabilty we can paralelize this structure in 2 threads, one for each axle
	//###################################################################################################
     	XfollowFunc(objx,imgWidth);
     	YfollowFunc(objy,imgHeight);
	//###################################################################################################
	gpio.GPIOreset();
    if(waitKey(20) == 27){
        break;
    }
    }
    return 0;
    }
  

