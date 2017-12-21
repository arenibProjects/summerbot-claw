// Pince header
#include "pince.hpp"

// Fonctions

/**
  *	Pince(lift Servo, uchar lift_speed, clamp Servo, uchar clamp_speed) 
  */
Pince::Pince(Servo *liftServo, unsigned char lt_speed, Servo *clampServo, unsigned char clp_speed){
	lift=liftServo;
	clamp=clampServo; 
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
	const char increment = (clamp->read() < pos ? 1 : -1);
	for (unsigned char i = clamp->read();i != pos;i += increment) {
		clamp->write(i);
		delay(clamp_speed);
	}
}
/**
  * load()
  */
void Pince::load(){
	setLiftPos(down);
	//capteur pos basse
	setClampPos(close);
	//capteur pos fermee
	setLiftPos(up);
	//capteur pos haute
}
/**
  * unload()
  */
void Pince::unload(){
	setClampPos(open);
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
