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
	motionTimer.begin(motionLoop,1000000);// 10kHz (100 is the period in microS)
	motionTimer.priority(1); //slightly above normal
  
	Serial.begin(9600);
	delay(5000);
		
	tmplift.attach(4);
	tmpClampL.attach(2);
	tmpClampR.attach(3);
	claw = new Claw(&tmplift,100,&tmpClampL,&tmpClampR,100);
	init = true;

}

void loop() {
	
	if(init) {
		
		Serial.println("resetLift");
		claw->moveLift(UP);	
		Serial.println(claw->movesString());
		Serial.println("resetClamp");
		claw->moveClamp(OPEN);
		Serial.println(claw->movesString());
		Serial.println("fin setup");
		claw->moveLift(DOWN);
		claw->moveClamp(CLOSE);
		init = false;
		
	}
	
	//claw->moveLift(DOWN);
	//claw->moveLift(UP)
	
	Serial.println(claw->movesString());
}

void motionLoop() {
	claw->update();
}
