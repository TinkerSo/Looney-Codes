#include <Servo.h>

#define L_MOTOR_PIN 8
#define R_MOTOR_PIN 12

Servo L_motor;
Servo R_motor;

int val = 0;
char command = 's';

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

  if(val == 200){
    command = 's';
    motorStop(L_motor);
    motorStop(R_motor);
    
  }
  else if(val == 201){
    command = 'f';
    motorControl(-100, L_motor);
    motorControl(100, R_motor);
  }
  else if(val == 202){
    command = 'b';
  }
  
  if(command == 's'){
    motorStop(L_motor);
    motorStop(R_motor);
  }
  else if(command == 'b'){
    motorControl(-val, L_motor);
    motorControl(val, R_motor);
  }
  else if(command == 'f'){
    motorControl(val, L_motor);
    motorControl(-val, R_motor);
  }

  
}
