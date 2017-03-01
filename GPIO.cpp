/***********************************************************
Universidade Lusiada de VN de Famalicão                    *
NTRI - tracking camera Proof Of Concept                    *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/

#include <WiringPi.h>

//top constructor
GPIO::GPIO(){
	WiringPiSetup();

	//constants representing the GPIO pinout numbers, designed from now on as ID.
	BaseA1 = 11;
	BaseA2 = 12;
	BaseB1 = 13;
	BaseB2 = 15;
 
	//CameraA1 =
	//CameraA2 =
	//CameraB1 =
	//CameraB2 =
}

//top destructor
GPIO::~GPIO(){
	//destructor of the instance, destroys the instance of the lib
	delete WiringPiSetup();
}


//Sets the mode for the coils of the base stepper
void GPIO::setGPIOpinModeBase(int const BaseA1, int const BaseA2, int const BaseB1, int const BaseB2){
	//GPIO pin mode setting
	pinMode(BaseA1 ,OUTPUT);
	pinMode(BaseA2 ,OUTPUT);
	pinMode(BaseB1 ,OUTPUT);
	pinMode(BaseB2 ,OUTPUT);

}

//sets the mode for the coils of the camera stepper
void GPIO::setGPIOpinModeCamera(int const Camera1,int const CameraA2,int const CameraB1,int const CameraB2){
	pinMode(CameraA1 ,OUTPUT);
	pinMode(CameraA2 ,OUTPUT);
	pinMode(CameraB1 ,OUTPUT);
	pinMode(CameraB2 ,OUTPUT);
}

//resets the GPIO pin state to a default of low (off); call before changing direction to avoid strange rotation behavior
void GPIO::GPIOreset(){
	digitalWrite(BaseA1, LOW);
	digitalWrite(BaseA2, LOW);
	digitalWrite(BaseB1, LOW);
	digitalWrite(BaseB2, LOW);
	digitalWrite(CameraA1, LOW);
	digitalWrite(CameraA2, LOW);
	digitalWrite(CameraB1, LOW);
	digitalWrite(CameraB2, LOW);
}

//@params: a, a1, b, and b1 are abstract integer constants, feed the desired IDs in the given order.
//first step sequence
void GPIO::step1(int const a, int const a1, int const b, int const b1){
	digitalWrite (a, HIGH);
    digitalWrite (a1,  LOW);
	digitalWrite (b,  LOW);
	digitalWrite (b1,  LOW); 
}
//next (second) step sequence
void GPIO::step2(int const a, int const a1, int const b, int const b1){
	digitalWrite (a, HIGH);
    digitalWrite (a1,  LOW);
	digitalWrite (b,  LOW);
	digitalWrite (b1,  LOW); 
}
//third step sequence
void GPIO::step3(int const a, int const a1, int const b, int const b1){
	digitalWrite (a, HIGH);
    digitalWrite (a1,  LOW);
	digitalWrite (b,  LOW);
	digitalWrite (b1,  LOW); 
}
//fourth step sequence
void GPIO::step4(int const a, int const a1, int const b, int const b1){
	digitalWrite (a, HIGH);
    digitalWrite (a1,  LOW);
	digitalWrite (b,  LOW);
	digitalWrite (b1,  LOW); 
}

//WARNING: Be sure to call the GPIOreset function before inverting directions.
//Full step sequence to rotate left
void sequenceL(int const a, int const a1, inst const b, int const b1){
	step1(a, a1, b, b1);
	step2(a, a1, b, b1);
	step3(a, a1, b, b1);
	step4(a, a1, b, b1);
}
//Full step sequence to rotate right (inversion of left)
void sequenceR(int const a, int const a1, inst const b, int const b1){
	step4(a,a1,b,b1);
	step3(a,a1,b,b1);
	step2(a,a1,b,b1);
	step1(a,a1,b,b1);
}