#include "PID.h"
#include <Arduino.h>

PID::PID(float P, float I, float D){
  kP = P;
  kI = I;
  kD = D;
}

void PID::updateTime(){
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
}

int PID::motorSpeed(int setpoint, int value){
  error = value;
  cumError += error*elapsedTime;
  rateError = (error-lastError)/elapsedTime;

  speed = kP*error + kI*cumError + kD*rateError;

  lastError= error;
  previousTime = currentTime;

  return speed;
}

void PID::setP(float val){
  kP = val;
}

void PID::setI(float val){
  kI = val;
}

void PID::setD(float val){
  kD = val;
}
