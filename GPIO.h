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
#ifndef PROCESSINGIMAGE_H
#define PROCESSINGIMAGE_H

#include <WiringPi.h>
#include <processingImage.h>
using namespace std;
using namespace WiringPi;

Class GPIO{

	public:
	GPIO();
	~GPIO();
	void setGPIOpinModeBase(int,int,int,int);
	void setGPIOpinModeCamera(int,int,int,int);
	void GPIOreset();
	void step1(const int,const int,const int,const int);
	void step2(const int,const int,const int,const int);
	void step3(const int,const int,const int,const int);
	void step4(const int,const int,const int,const int);
	void sequenceL();
	void sequenceR();
	
	//@params: BaseA1,BaseA2,BaseB1,BaseB2 are the pin numbers that will control de coils of the base stepper. In this context will be called IDs.
	int const BaseA1;
	int const BaseA2;
	int const BaseB1;
	int const BaseB2;
	//@params: CameraA1, CameraA2, CameraB1, CameraB2; are the pin numbers that will control de camera stepper. As stated above.
	int const CameraA1;
	int const CameraA2;
	int const CameraB1; 
	int const CameraB2;
};

#endif //WIRINGPI_H
#endif //PROCESSINGIMAGE_H