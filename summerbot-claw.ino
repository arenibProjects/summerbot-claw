#include "claw.hpp"
#include <Servo.h>

Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Pince* pince;

void setup() {
	tmplift.attach(9);
	tmpClampL.attach(10);
	tmpClampR.attach(11);
	Pince pince(&tmplift,220,&tmpClampL,&tmpClampR,220);
	Serial.begin(9600);
	pince.setLiftPos(0);
	pince.setClampPos(0);
	pince.load();
	delay(2000);
	pince.unload();
	delay(2000);
	pince.setLiftPos(90);
	pince.setClampPos(90);
}

void loop() {
	
}
