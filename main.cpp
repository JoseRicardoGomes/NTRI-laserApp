/***********************************************************
Universidade Lusiada de VN de Famalicão                    *
NTRI - tracking camera POC                                 *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/

#include "processingImage.cpp"
#include "GPIO.cpp"

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

int main()
{
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

      img = procImg.getImg();
      imgThreshold = procImg.getImgThreshold();

      imshow("ImageDisplay", img);
      imshow("ImageThreshold", imgThreshold);
      

	//TODO: Wrap the follow decision structure in it's own funtion
	//we can also define a new data structure with the sequences (left, right, up and down)
	//Possibly some sort of threshHold will be needed
	//###################################################################################################
	//for future scalabilty we can paralelize this structure in 2 threads one for each axle
	  
	if(procImg.posX < procImg.imgWidth / 2){
		//execute the left routine
		gpio.sequenceL();
	}
	else if(procImg.posX > procImg.imgWidth / 2){
		//execute the right routine
		gpio.sequenceR();
	}
	else if(procImg.posY < procImg.imgHeight / 2){
		//execute the down routine
		gpio.sequenceL();
	}
	else if(procImg.posY > procImg.imgHeight / 2){
		//execute the up routine
		gpio.sequenceR();
	}
	else{
		cout<< "Target located ready to deploy."<<endl;
		continue;
	}
	gpio.GPIOreset();
	 //################################################################################################### 
      if(waitKey(20) == 27)
        break;
    }

    return 0;

}