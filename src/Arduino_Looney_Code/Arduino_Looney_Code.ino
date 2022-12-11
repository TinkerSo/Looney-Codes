#include "motor.h"
#include "PID.h"

PID pid(0.9,0.005,0.001);


int totalError = 0;
int derivative;
int prevError = 0;
int Pvalue;
int Ivalue;
int Dvalue;
int speed;

#define L_MOTOR_PIN 8
#define R_MOTOR_PIN 12

int val = 0;

motor chassis;

void setup() {
  // put your setup code here, to run once:
  chassis.set_pins(R_MOTOR_PIN, L_MOTOR_PIN);
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // Allow for Serial to connect before reading
    val = Serial.read();
  }

  if(val>=100 && val<200){
    val = 100;
  }

  if(val<200){
    totalError += val;
    derivative = val - prevError;
    Pvalue = kp*val;
    Ivalue = ki*totalError;
    Dvalue = kd*derivative;
    if(Pvalue > 100){
      Pvalue = 100;
    }
    if(Ivalue > 100){
      Ivalue = 100;
    }
    if(Dvalue > 100){
      Dvalue = 100;
    }

  
    a=kpid.ComputMotorSpeed(val);
    cout<<"motor speed is"<<a<<endl;
     
    
    Serial.println(Ivalue);
    chassis.power(speed);

    prevError = val;
  }
  else{
    chassis.power(val);
    totalError = 0;
  }
  
