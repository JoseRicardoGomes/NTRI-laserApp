#include "processingImage.cpp"

using namespace std;
using namespace cv;

processingImage procImg;

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

    Mat img;
    Mat imgThreshold;

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

      if(waitKey(20) == 27)
        break;
    }

    return 0;

}
