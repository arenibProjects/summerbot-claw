// Pince header
#include "claw.hpp"

// Fonctions

/**
  *	Pince(lift Servo, uchar lift_speed, clamp Servo, uchar clamp_speed) 
  */
Pince::Pince(Servo *liftServo, unsigned char lt_speed, Servo *clpServoR, Servo *clpServoL, unsigned char clp_speed){
	lift=liftServo;
	clampServoLeft = clpServoR;
	clampServoRight = clpServoL;
	lift_speed=255-lt_speed;
	clamp_speed=255-clp_speed;
}
/**
  * setLiftPos(uchar pos)
  */

void Pince::setLiftPos(unsigned char pos) {
	const char increment = (lift->read() < pos ? 1 : -1);
	for (unsigned char i = lift->read();i != pos;i += increment) {
		lift->write(i);
		delay(lift_speed);
	}
}
/**
  * setClampPos( uchar pos)
  */

void Pince::setClampPos(unsigned char pos){
	const char increment = (clampServoLeft->read() < pos ? 1 : -1);
	for (unsigned char i = clampServoRight->read();i != pos;i += increment) {
		clampServoLeft->write(i);
		clampServoRight->write(i);
		delay(clamp_speed);
	}
}
/**
  * load()
  */
void Pince::load(){
	setLiftPos(DOWN);
	//capteur pos basse
	setClampPos(CLOSE);
	//capteur pos fermee
	setLiftPos(UP);
	//capteur pos haute
}
/**
  * unload()
  */
void Pince::unload(){
	setClampPos(OPEN);
	//capteur pos ouverte
}
/**
  * setClampSpeed
  */
void Pince::setClampSpeed(unsigned char clpSpeed){
	clamp_speed=255-clpSpeed;
}
/**
  * setLiftSpeed
  */
void Pince::setLiftSpeed(unsigned char ltSpeed){
	lift_speed=255-ltSpeed;
}
