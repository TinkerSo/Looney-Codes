#include "motor.h"
#include "PID.h"

PID pid(1.2, 0.002);  //PD

int chassis_speed;

#define L_MOTOR_PIN 8
#define R_MOTOR_PIN 12

int val = 0;

motor chassis;

void setup() {
  // setup code which runs once
  chassis.set_pins(R_MOTOR_PIN, L_MOTOR_PIN);
  Serial.begin(9600);
}



void loop() {
  // main code here that runs repeatedly:
  if (Serial.available() > 0) { 
    val = Serial.read();
  }


  if(val>=100 && val<200){
    val = 100;
  }

  chassis_speed = pid.ComputeMotorSpeed(val);
  
  if(val<200){ 
    chassis.power(chassis_speed);
  }
  else{
    chassis.power(val);
  }

}
