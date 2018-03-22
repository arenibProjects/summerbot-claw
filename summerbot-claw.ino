#include "claw.hpp"
#include <Servo.h>

IntervalTimer motionTimer;
Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Pince* pince;

void setup() {
	
	Serial.begin(9600);
	
	//Timer
	motionTimer.begin(motionLoop,100);// 10kHz (100 is the period in microS)
	motionTimer.priority(1); //slightly above normal
	
	tmplift.attach(9);
	tmpClampL.attach(10);
	tmpClampR.attach(11);
	Pince pince(&tmplift,220,&tmpClampL,&tmpClampR,220);
	
	Serial.println("resetPos");
	pince.setLiftPos(0);
	pince.setClampPos(0);
	
}

void loop() {
	
	while(pince->busy()){
		delay(500);
	}
	
	Serial.println("unload");
	pince->unload();
	Serial.println("load");
	pince->load();
	delay(1000);
	
}

void motionLoop() {
	pince->update();
	
}
