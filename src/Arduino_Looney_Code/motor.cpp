#include "motor.h"
#include "PID.h"

double kP = 0;
double kI = 1;
double kD = 0;

PID PID_control(kP, kI, kD);

motor::motor() {
  command = 's';
}

void motor::set_pins(int right_pin, int left_pin) {
  right_motor.attach(right_pin);
  left_motor.attach(left_pin);
}

void motor::motorControl(int value, Servo motor) {
  motor.write(map(value, -100, 100, 1000, 2000));
}

void motor::motorStop(Servo motor) {
  motor.write(0);
}

void motor::power(int val) {

  if (val == STOP) {
    command = 's';
    motorStop(left_motor);
    motorStop(right_motor);

  }
  else if (val == FORWARD) {
    command = 'f';
  }
  else if (val == BACKWARD) {
    command = 'b';
  }
  else if (val == LEFTTURN) {
    command = 'l';
  }
  else if (val == RIGHTTURN) {
    command = 'r';
  }

  if (command == 's') {
    motorStop(left_motor);
    motorStop(right_motor);
  }
  else if (command == 'b') {
    motorControl(-val, left_motor);
    motorControl(val, right_motor);
  }
  else if (command == 'f') {
    motorControl(val, left_motor);
    motorControl(-val, right_motor);
  }
  else if (command == 'l') {
    motorControl(-val, left_motor);
    motorControl(-val, right_motor);
  }
  else if (command == 'r') {
    motorControl(val, left_motor);
    motorControl(val, right_motor);
  }
}
