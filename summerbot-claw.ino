#include "claw.hpp"
#include <Servo.h>

IntervalTimer motionTimer;
Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw* claw;
bool init;

void setup() {

	//Timer
	motionTimer.begin(motionLoop,50000);// 10kHz (100 is the period in microS)
	motionTimer.priority(1); //slightly above normal
  
	Serial.begin(9600);
	delay(5000);
		
	tmplift.attach(4);
	tmpClampL.attach(3);
	tmpClampR.attach(2);
	claw = new Claw(&tmplift,&tmpClampL,&tmpClampR);
	delay(100);
	claw->init();
	Serial.println("Claw initilized");
	Serial.println("waiting 3s for motion to complete");
	delay(3000);
	init = false;

}

void loop() {
	
	if(init) {

		Serial.println("test");
		claw->moveLift(DOWN);
		claw->moveClamp(OPEN);
		claw->moveClamp(CLOSE);
		claw->moveLift(UP);
		init = false;
		
	}

}

void motionLoop() {

	claw->update();
	Serial.println(claw->getPos());

}
