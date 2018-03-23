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
	
}


//---Functions

/**
  * setLiftPos(uchar pos)
  */
void Pince::setLiftPos(unsigned char pos) {
	Move* mv = new Move(MoveType::Lift,pos);
    if(moves_)moves_->append(mv);
    else moves_ = mv;
}

/**
  * setClampPos(uchar pos)
  */
void Pince::setClampPos(unsigned char pos){
	Move* mv = new Move(MoveType::Clamp,pos);
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
	if(!moves_ && !isPaused) {
		if(moves_->type_ == MoveType::Lift){
			const int currentPos = lift->read();
			Serial.println(currentPos);
			if(millis() >= (1-liftSpeed)/liftSpeed*lastLiftTime) {
				const int increment = (currentPos < moves_->targPos_ ? 1 : -1);
				lift->write(currentPos + increment);
			}
		
			if(moves_->targPos_ == currentPos) {
				clearCurrentMove(moves_);
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
				clearCurrentMove(moves_);
			}
		}
	}
	
}

void clearCurrentMove () {
	Move* move = moves_;
	move = moves_->getNext();
	delete move;
}

bool Pince::isBusy() {
	return moves_;
}