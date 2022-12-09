#include "PID.h"
#include <Arduino.h>

PID::PID(double P, double I, double D) {
  kP = P;
  kI = I;
  kD = D;
  prevError = 0;
  totalError = 0;
}

void PID::updateTime() {
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
}

int PID::ComputMotorSpeed(int val) {
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


    speed = Pvalue + Ivalue + Dvalue;

    if (speed > 100) {
      speed = 100;
    }

    return speed;
  }

  void PID::setP(float val) {
    kP = val;
  }

  void PID::setI(float val) {
    kI = val;
  }

  void PID::setD(float val) {
    kD = val;
  }
