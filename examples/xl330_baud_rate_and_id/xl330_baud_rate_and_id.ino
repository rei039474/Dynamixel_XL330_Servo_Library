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

//Set the desired ID for your servo
int servoID = 2;  // 254: broadcast; id value: 0~253

// If you want to use hardware Serial instead, comment following lines
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // (RX, TX) both connected to the data pin of XL330


void setup() {
////Following lines are for resetting id and baud rate, comment if not needed
  //Factory Default 57,600[bps], if you have changed it before, set it to the one using to start communication.
  mySerial.begin(57600);  
  robot.begin(mySerial);
  
  robot.TorqueOFF(254);  //Servo needs to be torque off to change setting, broadcast to turn all servos off
  delay(50);

  // 254: broadcast ID; Available individual ID value: 0~253
  robot.setID(254, servoID);  //broadcast with 254, set one motor at a time to desired ID
  delay(50);
  
  //Baud Rate Options: 0: 9600; 1: 57600; 2: 115200; 3: 1M; 4: 2M; 5: 3M; 6: 4M
  robot.setBaudRate(254, 2);  //broadcast with 254, set one motor at a time to desired Baud Rate
  delay(50);
  
  Serial.end();  //End the original serial communication
  delay(50);


////Start the serial you're using
  //Restart the serial communication at the new Baud Rate on Line 45
  mySerial.begin(115200);
  robot.begin(mySerial);

  robot.TorqueON(servoID); //Turn on the torque to control the servo
  delay(50);
}

void loop() {
  //Blink LED as testing the new setting
  robot.LEDON(servoID);
  delay(500);
  robot.LEDOFF(servoID);
  delay(50);
}
