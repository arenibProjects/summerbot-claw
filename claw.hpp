#ifndef PINCE
#define PINCE 1

//Standard headers
#include <Arduino.h>
#include <Servo.h>

#define UP 0
#define DOWN 180
#define OPEN 0
#define CLOSE 180

class Pince {
public:
	Pince(Servo *liftServo, unsigned char lift_speed, Servo *clpServoR, Servo *clpServoL, unsigned char clamp_speed);
	void setLiftPos(unsigned char pos);
	void setClampPos(unsigned char pos);
	void load();
	void unload();
	void setLiftSpeed(unsigned char ltSpeed);
	void setClampSpeed(unsigned char clpSpeed);

private:
	Servo *lift;
	Servo *clampServoLeft;
	Servo *clampServoRight;
	unsigned char lift_speed;
	unsigned char clamp_speed;
};

#endif