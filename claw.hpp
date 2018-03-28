#ifndef PINCE_H
#define PINCE_H 1

//Standard headers
#include <Arduino.h>
#include <Servo.h>

#define UP 120
#define DOWN 110
#define OPEN 5
#define CLOSE 30
#define OFFSET 0

enum MoveType {
	None = 0,
	Lift = 1,
	Clamp = 2
};

class ClawMove {
	
    public:
	
        MoveType type_;
        int targPos_;
        ClawMove* next_ = 0;
        ClawMove(MoveType type,int targPos):type_{type},targPos_{targPos}{};
		
        ClawMove* getNext(){
            return next_;
        }
		
        ClawMove* getLast(){
            if(next_) return next_->getLast();
            else return this;
        }
		
        void append(ClawMove* nn){
            if(next_){
                next_->append(nn);
            }else{
                next_ = nn;
            }
        }
		
        void clear(){
            if(next_){
                next_->clear();
                delete next_;
            }
        }
		
        String toString(){
          return "|"+String(type_)+","+String(targPos_)+">";
        }
};

class Claw {

private:
		ClawMove *moves_;
	
	Servo *lift;
	Servo *clampLeft;
	Servo *clampRight;
	bool isPaused;

public:

	//initialisation
	Claw(Servo *liftServo, Servo *clpServoR, Servo *clpServoL);
	void init();
	
	//movements
	void moveLift(int moveAngle);
	void moveClamp(int moveAngle);
	void load();
	void unload();
	void stack();
	void openWide();
	void pause();
	void unpause();
	void clearMoves();
	void clearCurrentMove();

	//update
	void update();

	//infos
	bool isBusy();
	String movesString();
	String getPos();
};

#endif
