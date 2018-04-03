//---Pince header

#include "claw.hpp"


//---Constructor

/**
  	Pince(lift Servo, right clamp Servo, left clamp Servo)
*/
Claw::Claw(Servo *liftServo, Servo *clpServoR, Servo *clpServoL) {

  lift = liftServo;
  clampLeft = clpServoR;
  clampRight = clpServoL;
  isPaused = false;
  moves_ = NULL;

}


//---Functions

/**
    init()
*/
void Claw::init() {
  lift->write(0);
  delay(50);
  clampRight->write(0);
  delay(50);
  clampLeft->write(0);
  delay(50);
  lift->write(UP);
  delay(50);
  clampRight->write(CLOSE);
  delay(50);
  clampLeft->write(180 - CLOSE - OFFSET);
  delay(50);

}

/**
    moveLift(int pos)
*/
void Claw::moveLift(int targPos) {
  ClawMove* mv = new ClawMove(MoveType::Lift, targPos);
  if (moves_)moves_->append(mv);
  else moves_ = mv;
}

/**
    moveClamp(int pos)
*/
void Claw::moveClamp(int targPos) {

  // Serial.println("moveClamp");

  ClawMove* mv = new ClawMove(MoveType::Clamp, targPos);
  if (moves_)moves_->append(mv);
  else moves_ = mv;
}

/**
    load()
*/
void Claw::load() {

  moveLift(DOWN);
  moveClamp(CLOSE);
  moveLift(UP);

}

/**
    unload()
*/
void Claw::unload() {

  moveLift(DOWN);
  moveClamp(OPEN);
  moveLift(UP);

}

/**
    stack()
*/
void Claw::stack() {

  moveLift(DOWN);
  moveClamp(CLOSE - 1);
  moveClamp(CLOSE);
  moveLift(UP);

}

/**
    pause
*/
void Claw::pause() {

  isPaused = true;

}

/**
    unpause
*/
void  Claw::unpause() {

  if (isPaused) {
    isPaused = false;
  }

}

/**
    clearMoves
*/
void Claw::clearMoves() {
  moves_->clear();
}

/**
    update
*/
void Claw::update() {

  // Serial.println(moves_);
  // Serial.println("update");
  if (moves_ && !isPaused) {

    // Serial.println("not paused");
    //Serial.println(moves_->toString());

    if (moves_->type_ == MoveType::Lift) {

      // Serial.println("lift");

      const int currentPos = lift->read();

      // Serial.println(currentPos);

      const int increment = (moves_->targPos_ - currentPos > 0 ? SPEED : -SPEED);
      const int newPos = currentPos + increment;
      lift->write(newPos);
      if (abs(newPos - moves_->targPos_) < SPEED) {
        clearCurrentMove();
      }
    }

    if (moves_->type_ == MoveType::Clamp) {

      // Serial.println("clamp");

      const int currentPos = clampRight->read();

      // Serial.println(currentPos);

      const int increment = (moves_->targPos_ - currentPos > 0 ? SPEED : -SPEED);
      clampRight->write(currentPos + increment);
      clampLeft->write(180 - currentPos - OFFSET - increment);
      if (abs(currentPos + increment - moves_->targPos_) < SPEED) {
        clearCurrentMove();
      }
    }
  }
}

/**
    clearCurrentMove
*/
void Claw::clearCurrentMove () {

  ClawMove* mv = moves_;
  moves_ = moves_->getNext();
  delete mv;

}

/**
    openWide
*/
void Claw::openWide() {

  moveLift(UP);
  moveClamp(OPEN);

}

/**
    isBusy
*/
bool Claw::isBusy() {

  return moves_;
}

/**
    movesString
*/
String Claw::movesString() {

  String r = "";
  ClawMove* mv = moves_;
  while (mv) {
    r += mv->toString();
    mv = mv->getNext();
  }
  return r;
}

/**
    getPos
*/
String Claw::getPos() {

  String r = "lift : " + String(lift->read())
             + "| left clamp : " + String(clampLeft->read())
             + "| right clamp : " + String(clampRight->read());

  return r;
}
