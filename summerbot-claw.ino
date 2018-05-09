#include "claw.hpp"
#include "pinout.h"
#include <Servo.h>

IntervalTimer motionTimer;
Servo tmplift;
Servo tmpClampL;
Servo tmpClampR;
Claw* claw;
bool init;

void setup() {

  //Timer
  motionTimer.begin(motionLoop, 20000); // 10kHz (100 is the period in microS)
  motionTimer.priority(1); //slightly above normal

  Serial.begin(9600);
  delay(5000);

  tmplift.attach(SERVO1);
  tmpClampL.attach(SERVO6);
  tmpClampR.attach(SERVO7);
  claw = new Claw(&tmplift, &tmpClampL, &tmpClampR);
  delay(100);
  claw->init();
  Serial.println("Claw initilized");
  Serial.println("waiting .5s for motion to complete");
  delay(500);
  init = true;

}

void loop() {

  if (init) {

    Serial.println("down");
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    claw->moveLift(DOWN);
    while(claw->isBusy()) {
      delay(100);
    }
    delay(1000);
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    Serial.println("up");
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    claw->moveLift(UP);
    while(claw->isBusy()) {
      delay(100);
    }
    delay(1000);
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    Serial.println("close");
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    claw->moveClamp(CLOSE);
    while(claw->isBusy()) {
      delay(100);
    }
    delay(1000);
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    Serial.println("open");
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    claw->moveClamp(OPEN);
    while(claw->isBusy()) {
      delay(100);
    }
    delay(1000);
    Serial.println(claw->getPos());
    Serial.println(claw->movesString());
    /*claw->load();
    claw->unload();
    claw->load();
    claw->unload();
    claw->load();
    claw->unload();
    claw->load();
    claw->unload();
    Serial.println(claw->movesString());
    init = false;*/

  }

  //claw->moveLift(DOWN);
  //claw->moveLift(UP)

  // Serial.print("isBusy :");
  // Serial.println(claw->isBusy());

}

void motionLoop() {

  claw->update();
  //Serial.println(claw->movesString());
  //Serial.println(claw->getPos());
}
