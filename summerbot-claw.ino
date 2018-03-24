#include "claw.hpp"
#include <Servo.h>

IntervalTimer motionTimer;
Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Pince* pince;


void setup() {
	
	Serial.begin(9600);
	delay(5000);
	
	//Timer
	motionTimer.begin(motionLoop,5000);// 0.2Hz (5000 is the period in microS)
	motionTimer.priority(1);
	
	tmplift.attach(4);
	tmpClampL.attach(2);
	tmpClampR.attach(3);
	pince = new Pince(&tmplift,220,&tmpClampL,&tmpClampR,220);
	Serial.println("resetLift");
	pince->setLiftPos(UP);
	Serial.println(pince->movesString());
	Serial.println("resetClamp");
	pince->setClampPos(OPEN);
	Serial.println(pince->movesString());
	Serial.println("fin setup");

}

void loop() {
	
	Serial.println(pince->movesString());
	
	while(pince->isBusy()){
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
