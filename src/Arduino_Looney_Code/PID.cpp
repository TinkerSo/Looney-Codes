#include "PID.h"
#include <Arduino.h>

PID::PID(double P, double I, double D) {
  kP = P;
  kI = I;
  kD = D;
  prevError = 0;
  totalError = 0;
}
//overloaded because we want to use kP and kD still
PID::PID(double P, double D) {
  kP = P;
  kI = 0;
  kD = D;
  prevError = 0;
  totalError = 0;
}

void PID::updateTime() {
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
}

int PID::ComputeMotorSpeed(int val) {
  if (val < 200) {
    totalError += val;
    derivative = val - prevError;
    Pvalue = kP * val;
    Ivalue = kI * totalError;
    Dvalue = kD * derivative;

    if (Pvalue > 100) {
      Pvalue = 100;
    }
    if (Ivalue > 100) {
      Ivalue = 100;
    }
    if (Dvalue > 100) {
      Dvalue = 100;
    }


    computed_speed = Pvalue + Ivalue + Dvalue;

    if (computed_speed > 100) {
      computed_speed = 100;
    }

    prevError = val;

  }
  else if(val>=200){
    totalError = 0;
    //computed_speed = 0;
  }
  return computed_speed;
}

void PID::setP(double val) {
  kP = val;
}

void PID::setI(double val) {
  kI = val;
}

void PID::setD(double val) {
  kD = val;
}
