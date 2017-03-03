/***********************************************************
Universidade Lusiada de VN de Famalicão                    *
NTRI - tracking camera Proof Of Concept                    *
                                                           *
2016-2017                                                  *
                                                           *
By: Filipe Santos and JRG                                  *
***********************************************************/

#ifndef WIRINGPI_H
#define WIRINGPI_H

#include <wiringPi.h>

using namespace std;

class GPIO{

	public:
	GPIO();
	~GPIO();
	void setGPIOpinModeBase(int,int,int,int);
	void setGPIOpinModeCamera(int,int,int,int);
	void GPIOreset();
	void step1(int, int, int, int);
	void step2(int, int, int, int);
	void step3(int, int, int, int);
	void step4(int, int, int, int);
	void sequenceL(int, int, int, int);
	void sequenceR(int, int, int, int);
	void igitalWrite(int,int const);
	//@params: BaseA1,BaseA2,BaseB1,BaseB2 are the pin numbers that will control de coils of the base stepper. In this context will be called IDs.
	int BaseA1;
	int BaseA2;
	int BaseB1;
	int BaseB2;
	//@params: CameraA1, CameraA2, CameraB1, CameraB2; are the pin numbers that will control de camera stepper. As stated above.
	int CameraA1;
	int CameraA2;
	int CameraB1; 
	int CameraB2;
	
	int const H = 1;
	int const L = 0;
};

#endif //WIRINGPI_H