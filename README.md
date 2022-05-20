Dynamixel XL-330
================
This library is developed based on the code from [hackerspace-adelaide/XL320](https://github.com/hackerspace-adelaide/XL320). The modification is made by [Rei Lee](mailto:wl593@cornell.edu).


This is a library created to control Dynamixel XL-330 servos directly with microcontorllers without the need of Dynamixel U2D2 USB communication converter. It works for both [XL330-M077-T](https://emanual.robotis.com/docs/en/dxl/x/xl330-m077/) and [XL330-M288-T](https://emanual.robotis.com/docs/en/dxl/x/xl330-m288/) models and has been tested with Arduino and ESP32 boards. Please refer to Dynamixel website for more info about the servos.


<img src="https://emanual.robotis.com/assets/images/dxl/x/xl330_temp/xl330-series_product.png" width="50%" alt="Dynamixel XL-330 servo" title="Dynamixel XL-330 servo">


**It is still work in progress... not ready yet, but can be used for simple control.**

================

<img src="XL330_wire_Arduino.jpg" width="100%" alt="Dynamixel XL-330 servo library for microcontroller" title="Dynamixel XL-330 servo library for microcontroller">

## A XL-330 Servo library for Arduino

Clone this repository into your Arduino IDE libraries folder:

``` $ cd ~/Documents/Arduino/libraries/ ```

Restart Arduino IDE after. Open the example Arduino sketch to see how it works:

``` File > Examples > XL330 > XL330_servo_example ```


### Hardware

[DYNAMIXEL XL-320 servo manual](http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm) including specifications and message sending addresses.


### Wiring diagram

Looking from above, with the servo head at the top, wire the left plug of the servo to:

* PIN1: GND
* PIN2: 5 volts
* PIN3: Serial TX

![Dynamixel XL-320 wiring diagram](XL320-wiring.jpg)

### Setting the servo serial baud rate & servoID

We've included some example sketches to help test and setup your servos. Out of the box they're set to communicate via serial at 1Mbps, so you might want to set them down to something more managable by Arduino at 115200.

Follow the instructions in the sketch ```XL320_servo_set_baud_rate_or_id.ino``` and don't forget to power cycle the servos in between setting anything.

Note: when setting the ServoID, the servos default down to 9600 baud, so after you set the servoID you'll need to set the baud rate back up to 115200.

### More information

Read more about this library on the [Hackerspace Adelaide Wiki](http://hackerspace-adelaide.org.au/wiki/Dynamixel_XL-320)
