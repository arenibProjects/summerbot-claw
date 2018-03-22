// Pince header
#include "claw.hpp"

// Fonctions

/**
  *	Pince(lift Servo, uchar lift_speed, clamp Servo, uchar clamp_speed) 
  */
Pince::Pince(Servo *liftServo, unsigned char lt_speed, Servo *clpServoR, Servo *clpServoL, unsigned char clp_speed){
	lift=liftServo;
	clampLeft = clpServoR;
	clampRight = clpServoL;
	liftSpeed = 255 - lt_speed;
	clampSpeed = 255 - clp_speed;
	lastClampTime = millis();
	lastLiftTime = millis();
	moves.clear();
	isPaused = false;
	
}

/**
  * setLiftPos(uchar pos)
  */
void Pince::setLiftPos(unsigned char pos) {
	addMove(moves,MoveType::Lift,pos);
}

/**
  * setClampPos(uchar pos)
  */
void Pince::setClampPos(unsigned char pos){
	addMove(moves,MoveType::Clamp,pos);
}

/**
  * load()
  */
void Pince::load(){
	
	setLiftPos(DOWN);
	setClampPos(CLOSE);
	setLiftPos(UP);

}

/**
  * unload()
  */
void Pince::unload(){
	setClampPos(OPEN);
}

/**
  * pause
  */
void Pince::pause() {
	isPaused = true;
}

/**
  * unpause
  */
void  Pince::unpause() {
	if(isPaused) {
		isPaused = false;
	}
}

/**
  * clearMoves
  */
void Pince::clearMoves() {
	moves.clear();
}

/**
  * setClampSpeed
  */
void Pince::setClampSpeed(unsigned char clpSpeed){
	clampSpeed=255-clpSpeed;
}

/**
  * setLiftSpeed
  */
void Pince::setLiftSpeed(unsigned char ltSpeed){
	liftSpeed=255-ltSpeed;
}

void Pince::update() {
	if(!moves.empty() && !isPaused) {
		if(moves.front().type == MoveType::Lift){
			const int currentPos = lift->read();
			if(millis() >= (1-liftSpeed)/liftSpeed*lastLiftTime) {
				const int increment = (currentPos < moves.front().targPos ? 1 : -1);
				lift->write(currentPos + increment);
			}
		
			if(moves.front().targPos == currentPos) {
				clearCurrentMove(moves);
			}
		}
	
		if(moves.front().type == MoveType::Clamp){
			const int currentPos = clampRight->read();
			if(millis() >= (1-clampSpeed)/clampSpeed*lastClampTime) {
				const int increment = (currentPos < moves.front().targPos ? 1 : -1);
				clampRight->write(currentPos + increment);
				clampLeft->write(currentPos + increment);
			}
		
			if(moves.front().targPos == currentPos) {
				clearCurrentMove(moves);
			}
		}
	}
	
}

void Pince::clearCurrentMove(std::vector<Move> &moves) {
	const int size = moves.size();
	for (int i=1; i<size; i++) {
		moves[i-1] = moves[i];
	}
}

bool Pince::busy() {
	return moves.empty();
}
