//---Pince header

#include "claw.hpp"


//---Constructor

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
	isPaused = false;
	moves_ = NULL;
	
}


//---Functions

/**
  * setLiftPos(uchar pos)
  */
void Pince::setLiftPos(unsigned char pos) {
	ClawMove* mv = new ClawMove(MoveType::Lift,pos);
    if(moves_)moves_->append(mv);
    else moves_ = mv;
}

/**
  * setClampPos(uchar pos)
  */
void Pince::setClampPos(unsigned char pos){
	ClawMove* mv = new ClawMove(MoveType::Clamp,pos);
    if(moves_)moves_->append(mv);
    else moves_ = mv;
	
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
	moves_->clear();
}

/**
  * movesString
  */
String Pince::movesString(){
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
	
	void Pince::clearCurrentMove () {
		ClawMove* mv = moves_;
		moves_ = moves_->getNext();
		delete mv;
	}

	bool Pince::isBusy() {
		return moves_;
	}
