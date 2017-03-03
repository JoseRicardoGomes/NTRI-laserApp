/***********************************************************
Universidade Lusiada de VN de Famalic�o                    *
NTRI - tracking camera Proof Of Concept                    *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/

#include "GPIO.h"

//top constructor
GPIO::GPIO(){
	//constants representing the GPIO pinout numbers, designed from now on as ID.
	BaseA1 = 11;
	BaseA2 = 12;
	BaseB1 = 13;
	BaseB2 = 15;

	CameraA1 = 29;
	CameraA2 = 31;
	CameraB1 = 33;
	CameraB2 = 35;
}

//top destructor
GPIO::~GPIO(){
	//destructor of the instance, destroys the instance of the lib
	//yes, empty, let the compiler do the job
}

//Sets the mode for the coils of the base stepper
void GPIO::setGPIOpinModeBase(int BaseA1, int BaseA2, int BaseB1, int BaseB2){
	//GPIO pin mode setting
	pinMode(BaseA1 ,OUTPUT);
	pinMode(BaseA2 ,OUTPUT);
	pinMode(BaseB1 ,OUTPUT);
	pinMode(BaseB2 ,OUTPUT);

}

//sets the mode for the coils of the camera stepper
void GPIO::setGPIOpinModeCamera(int Camera1,int CameraA2,int CameraB1,int CameraB2){
	pinMode(CameraA1 ,OUTPUT);
	pinMode(CameraA2 ,OUTPUT);
	pinMode(CameraB1 ,OUTPUT);
	pinMode(CameraB2 ,OUTPUT);
}

//resets the GPIO pin state to a default of low (off); call before changing direction to avoid strange rotation behavior
void GPIO::GPIOreset(){
	digitalWrite(BaseA1, L);
	digitalWrite(BaseA2, L);
	digitalWrite(BaseB1, L);
	digitalWrite(BaseB2, L);
	digitalWrite(CameraA1, L);
	digitalWrite(CameraA2, L);
	digitalWrite(CameraB1, L);
	digitalWrite(CameraB2, L);
}

//@params: a, a1, b, and b1 are abstract integer constants, feed the desired IDs in the given order.
//first step sequence
void GPIO::step1(int a, int a1, int b, int b1){
	digitalWrite (a, L);
	digitalWrite (a1,  H);
	digitalWrite (b,  H);
	digitalWrite (b1,  L);
}
//next (second) step sequence
void GPIO::step2(int a, int a1, int b, int b1){
	digitalWrite (a, L);
	digitalWrite (a1,  H);
	digitalWrite (b,  L);
	digitalWrite (b1,  H);
}
//third step sequence
void GPIO::step3(int a, int a1, int b, int b1){
	digitalWrite (a, H);
	digitalWrite (a1,  L);
	digitalWrite (b,  L);
	digitalWrite (b1,  H);
}
//fourth step sequence
void GPIO::step4(int a, int a1, int b, int b1){
	digitalWrite (a, H);
	digitalWrite (a1,  L);
	digitalWrite (b,  H);
	digitalWrite (b1,  L);
}

//WARNING: Be sure to call the GPIOreset function before inverting directions.
//Full step sequence to rotate left
void GPIO::sequenceL(int a, int a1, int b, int b1){
	step1(a,a1,b,b1);
	step2(a,a1,b,b1);
	step3(a,a1,b,b1);
	step4(a,a1,b,b1);
}
//Full step sequence to rotate right (inversion of left)
void GPIO::sequenceR(int a, int a1, int b, int b1){
	step3(a,a1,b,b1);
	step2(a,a1,b,b1);
	step1(a,a1,b,b1);
	step4(a,a1,b,b1);
}
