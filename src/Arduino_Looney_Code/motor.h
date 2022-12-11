#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

enum commandStates{
  STOP = 200,
  FORWARD = 201,
  BACKWARD = 202,
  LEFTTURN = 203,
  RIGHTTURN = 204
};

class motor{
  private:
    char command;
    Servo left_motor;
    Servo right_motor;
  
  public:
    motor();
    void set_pins(int right_pin, int left_pin);
    void motorControl(int value, Servo motor);
    void motorStop(Servo motor);
    void power(int val);
    
};

#endif
