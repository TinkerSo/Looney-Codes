# Looney-Codes
![logo](https://user-images.githubusercontent.com/113651019/207221817-925f1e45-c599-48c3-ae72-87bf9a1b2afc.jpeg)

Contactlass hand tracking motorized cart: May the force be with you
- [Demo Video](https://drive.google.com/file/d/1KN_9ofICUXL42smD-FLyvRaEv8-JSHKU/view)
- [Gantt Chart Timeline](https://docs.google.com/spreadsheets/d/1zjltLZRq7k2SDtg1kTdfaO2rv2rXiqlv2vjbMqw8aOY/edit?usp=sharing)

## Team Members
- Beren Donmez(bydonmez@bu.edu)
- Jiahe Niu (jniu@bu.edu)
- Christian So (cbso@bu.edu)

## Contents
- src/
  - Processing_Looney_Code
  - Arduino_Looney_Code
    - PID class: Propotional Inegral Derivative Control. This class smoothes out the movement of the chassis. It allows the system to react to sudden hand movement and stabalize its behavior.
    - Motor class: Using the command received from the Processing Code, the direction of the motors are determined and changed. Pulse width modulation (PWM) was mapped to Servo (an object from imported library) in order to control the motors. 
- doc/
  - Gantt Chart
  - Project Documentation
  - Project Architecture
  - Statement of Work

## Hardware
- LeapMotion Controller
- Arduino Uno PC
- 393 Vex Motors

## Software 
- Arduino IDE
- Processing 3

## Dependency
- Download [LeapMotion](https://developer.leapmotion.com/releases/leap-motion-orion-410-99fe5-crpgl)
- Download [Processing 3](https://processing.org/download)
- Download [Arduino IDE](https://www.arduino.cc/en/software)
