#include "claw.hpp"
#include <Servo.h>

IntervalTimer motionTimer;
Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw* claw;


void setup() {
	
	Serial.begin(9600);
	delay(5000);
	
	//Timer
	motionTimer.begin(motionLoop,5000);// 0.2Hz (5000 is the period in microS)
	motionTimer.priority(1);
	
	tmplift.attach(4);
	tmpClampL.attach(2);
	tmpClampR.attach(3);
	claw = new Claw(&tmplift,220,&tmpClampL,&tmpClampR,220);
	Serial.println("resetLift");
	claw->moveLift(UP);
	Serial.println(claw->movesString());
	Serial.println("resetClamp");
	claw->moveClamp(OPEN);
	Serial.println(claw->movesString());
	Serial.println("fin setup");

}

void loop() {
	
	Serial.println(claw->movesString());
	
	while(claw->isBusy()){
		delay(500);
	}
	
	Serial.println("unload");
	claw->unload();
	Serial.println("load");
	claw->load();
	delay(1000);
	
}

void motionLoop() {
	claw->update();
	
}
