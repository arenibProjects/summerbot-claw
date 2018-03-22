#ifndef PINCE_H
#define PINCE_H 1

//Standard headers
#include <Arduino.h>
#include <Servo.h>
#include <vector>

#define UP 0
#define DOWN 180
#define OPEN 0
#define CLOSE 180

class Pince {

private:

	enum MoveType {
		None = 0,
		Lift = 1,
		Clamp = 2,
		Paused = 0
	};
	
	struct Move {
		MoveType type;
		unsigned char targPos;
	};
	
	std::vector<Move> moves;
	
	Servo *lift;
	Servo *clampLeft;
	Servo *clampRight;
	unsigned char liftSpeed;
	unsigned char clampSpeed;
	double lastClampTime;
	double lastLiftTime;
	bool isPaused;
	
	void
	clearCurrentMove(std::vector<Move> &moves);
	
	inline void
	addMove(std::vector<Move> &moves, MoveType type, unsigned char pos) {
		Move move{type,pos};
		moves.emplace_back(std::move(move));
	}

public:

	Pince(Servo *liftServo, unsigned char lift_speed, Servo *clpServoR, Servo *clpServoL, unsigned char clamp_speed);
	void setLiftPos(unsigned char pos);
	void setClampPos(unsigned char pos);
	void load();
	void unload();
	void pause();
	void unpause();
	void clearMoves();
	void setClampSpeed(unsigned char clpSpeed);
	void setLiftSpeed(unsigned char ltSpeed);
	void update();
	bool busy();

};

#endif