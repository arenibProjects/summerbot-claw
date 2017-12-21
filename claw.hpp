#ifndef PINCE
#define PINCE 1

//Standard headers
#include <Arduino.h>
#include <Servo.h>
#include <math.h>

class Pince {
public:
	Pince(Servo *liftServo, unsigned char lift_speed, Servo *clampServo, unsigned char clamp_speed);
	void setLiftPos(unsigned char pos);
	void setClampPos(unsigned char pos);
	void load();
	void unload();
	void setLiftSpeed(unsigned char ltSpeed);
	void setClampSpeed(unsigned char clpSpeed);

private:
	unsigned char up = 0;
	unsigned char down = 180;
	unsigned char open = 0;
	unsigned char close = 180;
	Servo *lift;
	Servo *clamp;
	unsigned char lift_speed;
	unsigned char clamp_speed;
};

#endif