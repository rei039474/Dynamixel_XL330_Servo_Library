/*
 * Code based on:
 * Dynamixel.cpp - Ax-12+ Half Duplex UART Comunication
 * Copyright (c) 2011 Savage Electronics.
 * And Dynamixel Pro library for OpenCM-9.04 made by ROBOTIS, LTD.
 * And Luis G III for HelloSpoon robot (http://hellospoonrobot.com).
 * And hackerspace-adelaide/XL320 (https://github.com/hackerspace-adelaide/XL320).
 * 
 * Modified to work only with Dynamixel XL-330 actuator.
 * 
 * Modifications made by Rei Lee
 * Webpage: https://infosci.cornell.edu/~reilee/
 * Email: wl593@cornell.edu
 * 
 * This file can be used and be modified by anyone, 
 * don't forget to say thank you to OP!
 */
 
#include <XL330.h>

XL330 robot;  // Name your robot

int servoID = 1;  // 254: broadcast; id value: 0~252

// If you want to use Software Serial instead, uncomment following lines
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // (RX, TX) both connected to the data pin of XL330

#define readPin A0 //define potentiometer Pin

void setup() {
  
  pinMode(readPin, INPUT); //set potentiometer Pin as input pin


////Start the serial you're using
  mySerial.begin(115200);
  robot.begin(mySerial);
  
  robot.TorqueOFF(servoID); //Servo needs to be torque off to change setting, broadcast to turn all servos off
  delay(100);

  //Set the mode to position control
  //Control Mode Options: 0: current; 1: velocity; 3: position; 4: extended position; 5: current-base position; 16: PWM
  robot.setControlMode(servoID, 3);
  delay(50);

  robot.TorqueON(servoID);  //Turn on the torque to control the servo
  delay(50);

  //Blink LED as testing
  robot.LEDON(servoID);
  delay(500);
  robot.LEDOFF(servoID);
  delay(50);
}

void loop() {  
  //// Position-control (control mode 3) testing with potentiometer
  //// The value range for XL330 position control is 0 ~ 4095 mapping 0 ~ 360 [°]
  int pinRead = map(analogRead(A0), 0, 1023, 0, 4095); // mapping the potentiometer reading to value range of XL330
  robot.setJointPosition(servoID, pinRead);
  delay(100);
}
