#include "pince.hpp"
#include <Servo.h>

Servo tmplift;
Servo tmpclamp;
Pince* pince;

void setup() {
	tmplift.attach(9);
	tmpclamp.attach(10);
	Pince pince(&tmplift,220,&tmpclamp,220);
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
