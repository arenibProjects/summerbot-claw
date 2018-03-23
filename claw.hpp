#ifndef PINCE_H
#define PINCE_H 1

//Standard headers
#include <Arduino.h>
#include <Servo.h>

#define UP 0
#define DOWN 30
#define OPEN 0
#define CLOSE 70

enum MoveType {
	None = 0,
	Lift = 1,
	Clamp = 2
};

class Move {
	
    public:
        MoveType type_;
        unsigned char targPos_;
        Move* next_=0;
        Move(MoveType type,unsigned char targPos):type_{type},targPos_{targPos}{};
        Move* getNext(){
            return next_;
        }
        Move* getLast(){
            if(next_) return next_->getLast();
            else return this;
        }
        void append(Move* nn){
            if(next_){
                next_->append(nn);
            }else{
                next_ = nn;
            }
        };
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

class Pince {

private:
		Move *moves_ = (Move*)0;
	
	Servo *lift;
	Servo *clampLeft;
	Servo *clampRight;
	unsigned char liftSpeed;
	unsigned char clampSpeed;
	double lastClampTime;
	double lastLiftTime;
	bool isPaused;

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
	void clearCurrentMove(Move* mv); 
	bool isBusy();

};

#endif