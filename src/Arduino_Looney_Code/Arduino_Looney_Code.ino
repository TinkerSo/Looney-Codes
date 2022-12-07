#include "motor.h"

#define L_MOTOR_PIN 8
#define R_MOTOR_PIN 12

int val = 0;

motor chassis;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  chassis.set_pins(R_MOTOR_PIN, L_MOTOR_PIN);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // Allow for Serial to connect before reading
    val = Serial.read();
  }
  Serial.println(val);

  chassis.power(val);
  
}
