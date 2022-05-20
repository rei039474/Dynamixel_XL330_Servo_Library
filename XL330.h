/*
 * Code based on:
 * Dynamixel.cpp - Ax-12+ Half Duplex USART Comunication
 * Copyright (c) 2011 Savage Electronics.
 * And Dynamixel Pro library for OpenCM-9.04 made by ROBOTIS, LTD.
 * And Luis G III for HelloSpoon robot (http://hellospoonrobot.com).
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

#ifndef XL330_H_
#define XL330_H_

/*EEPROM Area*/
#define XL_MODEL_NUMBER_L           0
#define XL_MODEL_NUMBER_H           1
#define XL_MODEL_INFO               2
#define XL_VERSION                  6
#define XL_ID                       7
#define XL_BAUD_RATE                8
#define XL_RETURN_DELAY_TIME        9
#define XL_DRIVE_MODE               10
#define XL_CONTROL_MODE             11
#define XL_SECONDARY_ID             12
#define XL_PROTOCOL_TYPE            13
#define XL_HOMING_OFFSET            20
#define XL_MOVING_THRESHOLD         24
#define XL_TEMPERATURE_LIMIT        31
#define XL_MAX_VOLTAGE_LIMIT        32
#define XL_MIN_VOLTAGE_LIMIT        34
#define XL_PWM_LIMIT                36
#define XL_CURRENT_LIMIT            38
#define XL_VELOCITY_LIMIT           44
#define XL_MAX_POSITION_LIMIT       48
#define XL_MIN_POSITION_LIMIT       52
#define XL_STARTUP_CONFIGURATION    60
#define XL_PWM_SLOPE                62
#define XL_SHUTDOWN                 63
/*RAM Area*/
#define XL_TORQUE_ENABLE            64
#define XL_LED                      65
#define XL_STATUS_RETURN_LEVEL      68
#define XL_REGISTERED_INSTRUCTION   69
#define XL_HARDWARE_ERROR_STATUS    70
#define XL_VELOCITY_I_GAIN      	76
#define XL_VELOCITY_P_GAIN    		78
#define XL_POSITION_D_GAIN    	    80
#define XL_POSITION_I_GAIN      	82
#define XL_POSITION_P_GAIN    		84
#define XL_FEEDFORWARD_2ND_GAIN    	88
#define XL_FEEDFORWARD_1ST_GAIN 	90
#define XL_BUS_WATCHDOG			 	98
#define XL_GOAL_PWM                 100
#define XL_GOAL_CURRENT             102
#define XL_GOAL_VELOCITY            104
#define XL_PROFILE_ACCELERATION     108
#define XL_PROFILE_VELOCITY         112
#define XL_GOAL_POSITION            116
#define XL_REALTIME_TICK            120
#define XL_MOVING                   122
#define XL_MOVING_STATUS            123
#define XL_PRESENT_PWM              124
#define XL_PRESENT_CURRENT          126
#define XL_PRESENT_VELOCITY         128
#define XL_PRESENT_POSITION         132
#define XL_VELOCITY_TRAJECTORY      136
#define XL_POSITION_TRAJECTORY      140
#define XL_PRESENT_INPUT_VOLTAGE    144
#define XL_PRESENT_TEMPERATURE      146
#define XL_BACKUP_READY             147

#include <inttypes.h>
#include <Stream.h>

class XL330 {
private:
	unsigned char Direction_Pin;
	volatile char gbpParamEx[130+10];
	Stream *stream;

  void nDelay(uint32_t nTime);


public:
	XL330(); 
	virtual ~XL330();	
	
	void begin(Stream &stream);
	
	void setBaudRate(int id, int value);
	void setID(int id, int value);
	void setControlMode(int id, int value);
	
	void setJointPosition(int id, int value);
	void setJointSpeed(int id, int value);
	
	void LEDON(int id);
	void LEDOFF(int id);
	void TorqueON(int id);
	void TorqueOFF(int id);

	int getJointPosition(int id);
	int getJointSpeed(int id);
	int getJointTemperature(int id);
	int isJointMoving(int id);

	int sendPacket(int id, int Address, int value);
	int readPacket(unsigned char *buffer, size_t size);
	int sendPacket_4bytes(int id, int Address, int value);
	int sendPacket_1byte(int id, int Address, int value);

	int RXsendPacket(int id, int Address);
	int RXsendPacket(int id, int Address, int size);

	int flush();

	class Packet {
	  bool freeData;
	  public:
	    unsigned char *data;
	    size_t data_size;

	    // wrap a received data stream in an Packet object for analysis
	    Packet(unsigned char *data, size_t size);
	    // build a packet into the pre-allocated data array
	    // if data is null it will be malloc'ed and free'd on destruction.
	    
	    Packet(
	      unsigned char *data, 
	      size_t        size,
	      unsigned char id,
	      unsigned char instruction,
	      int           parameter_data_size,
	      ...);
	    ~Packet();
	    unsigned char getId();
	    int getLength();
	    int getSize();
	    int getParameterCount();
	    unsigned char getInstruction();
            unsigned char getParameter(int n);
	    bool isValid();

	    void toStream(Stream &stream);

	};
};

#endif
