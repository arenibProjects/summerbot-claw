//---Pince header

#include "claw.hpp"


//---Constructor

/**
  *	Pince(lift Servo, uchar lift_speed, clamp Servo, uchar clamp_speed) 
  */
Claw::Claw(Servo *liftServo, unsigned char lt_speed, Servo *clpServoR, Servo *clpServoL, unsigned char clp_speed){

	lift=liftServo;
	clampLeft = clpServoR;
	clampRight = clpServoL;
	liftSpeed = 255 - lt_speed;
	clampSpeed = 255 - clp_speed;
	lastClampTime = millis();
	lastLiftTime = millis();
	isPaused = false;
	moves_ = NULL;
	
}


//---Functions

/**
  * moveLift(uchar pos)
  */
void Claw::moveLift(unsigned char pos) {
	if(lift->read() != pos) {
		ClawMove* mv = new ClawMove(MoveType::Lift,pos);
		if(moves_)moves_->append(mv);
		else moves_ = mv;
	}
}

/**
  * moveClamp(uchar pos)
  */
void Claw::moveClamp(unsigned char pos){
	if(clampRight->read() != pos) {
		ClawMove* mv = new ClawMove(MoveType::Clamp,pos);
		if(moves_)moves_->append(mv);
		else moves_ = mv;
	}
}

/**
  * load()
  */
void Claw::load(){
	
	moveLift(DOWN);
	moveClamp(CLOSE);
	moveLift(UP);

}

/**
  * unload()
  */
void Claw::unload(){
	
	moveLift(DOWN);
	moveClamp(OPEN);
	moveLift(UP);

}

/**
  * pause
  */
void Claw::pause() {
	isPaused = true;
}

/**
  * unpause
  */
void  Claw::unpause() {
	if(isPaused) {
		isPaused = false;
	}
}

/**
  * clearMoves
  */
void Claw::clearMoves() {
	moves_->clear();
}

/**
  * movesString
  */
String Claw::movesString(){
  String r="";
  ClawMove* mv =moves_;
  while(mv){
    r+=mv->toString();
    mv=mv->getNext();
  }
  return r;
}

/**
  * setClampSpeed
  */
void Claw::setClampSpeed(unsigned char clpSpeed){
	clampSpeed=255-clpSpeed;
}

/**
  * setLiftSpeed
  */
void Claw::setLiftSpeed(unsigned char ltSpeed){
	liftSpeed=255-ltSpeed;
}

void Claw::update() {
	
	if(moves_) {
		Serial.println(moves_->toString());
	}
	
	if(moves_ && !isPaused) {
		if(moves_->type_ == MoveType::Lift){
			const int currentPos = lift->read();
			Serial.println(currentPos);
			if(millis() >= (1-liftSpeed)/liftSpeed*lastLiftTime) {
				const int increment = (currentPos < moves_->targPos_ ? 1 : -1);
				lift->write(currentPos + increment);
			}
		
			if(moves_->targPos_ == currentPos) {
				clearCurrentMove();
			}
		}
	
		if(moves_->type_ == MoveType::Clamp){
			const int currentPos = clampRight->read();
			Serial.println(currentPos);
			if(millis() >= (1-clampSpeed)/clampSpeed*lastClampTime) {
				const int increment = (currentPos < moves_->targPos_ ? 1 : -1);
				clampRight->write(currentPos + increment);
				clampLeft->write(currentPos - increment);
			}
		
			if(moves_->targPos_ == currentPos) {
				clearCurrentMove();
			}
		}
	}
}
	
void Claw::clearCurrentMove () {
	ClawMove* mv = moves_;
	moves_ = moves_->getNext();
	delete mv;
}

bool Claw::isBusy() {
	return moves_;
}
