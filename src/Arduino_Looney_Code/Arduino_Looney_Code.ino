#include <Servo.h>

#define L_MOTOR_PIN 8
#define R_MOTOR_PIN 12

Servo L_motor;
Servo R_motor;

char val;

void setup() {
  // put your setup code here, to run once:
  L_motor.attach(L_MOTOR_PIN);
  R_motor.attach(R_MOTOR_PIN);
  Serial.begin(9600);
 
}

void motorControl(int value, Servo motor) {
  motor.write(map(value, -100, 100, 1000, 2000));
}

void motorStop(Servo motor){
  motor.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // Allow for Serial to connect before reading
    val = Serial.read();
  }
  Serial.println(val);
  if(val == '1'){
    motorControl(40, L_motor);
    motorControl(-40, R_motor);
  }
  else if(val == '2'){
    motorControl(-40, L_motor);
    motorControl(40, R_motor);
  }
  else{
    motorStop(L_motor);
    motorStop(R_motor);
  }
 
  
}
