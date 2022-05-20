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

#include "Arduino.h"
#include "dxl_pro.h"
#include "XL330.h"
#include <stdlib.h>
#include <stdarg.h>

 // Macro for the selection of the Serial Port
#define sendData(args)  (this->stream->write(args))    // Write Over Serial
#define beginCom(args)      // Begin Serial Comunication
#define readData()		(this->stream->read())	

// Select the Switch to TX/RX Mode Pin
#define setDPin(DirPin,Mode)    
#define switchCom(DirPin,Mode)   // Switch to TX/RX Mode
#define NANO_TIME_DELAY 12000


XL330::XL330() {

}

XL330::~XL330() {
}

void XL330::begin(Stream& stream) {
	//setDPin(Direction_Pin=4,OUTPUT);
	//beginCom(1000000);
	this->stream = &stream;
}

void XL330::setBaudRate(int id, int value) {
	// 0: 9600; 1: 57600; 2: 115200; 3: 1M; 4: 2M; 5: 3M; 6: 4M (bps)
	int Address = XL_BAUD_RATE;

	sendPacket_1byte(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::setID(int id, int value) {
	// 254: broadcast; id value: 0~252
	int Address = XL_ID;

	sendPacket_1byte(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::setControlMode(int id, int value) {
	// 0: current control; 1: velocity control; 3: position control; 4: extended position control; 5: current-base position control; 16: PWM control
	int Address = XL_CONTROL_MODE;

	sendPacket_1byte(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::setJointPosition(int id, int value) {
	int Address = XL_GOAL_POSITION;

	sendPacket_4bytes(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::setJointSpeed(int id, int value) {
	int Address = XL_GOAL_PWM;

	sendPacket(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::LEDON(int id) {
	int Address = XL_LED;
	int val = 1;

	sendPacket_1byte(id, Address, val);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::LEDOFF(int id) {
	int Address = XL_LED;
	int val = 0;

	sendPacket_1byte(id, Address, val);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::TorqueON(int id) {
	int Address = XL_TORQUE_ENABLE;
	int value = 1;

	sendPacket_1byte(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

void XL330::TorqueOFF(int id) {
	int Address = XL_TORQUE_ENABLE;
	int value = 0;

	sendPacket_1byte(id, Address, value);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
}

int XL330::getJointPosition(int id) {
	unsigned char buffer[255];
	RXsendPacket(id, XL_PRESENT_POSITION, 2);
	this->stream->flush();
	if (this->readPacket(buffer, 255) > 0) {
		Packet p(buffer, 255);
		if (p.isValid() && p.getParameterCount() >= 3) {
			return (p.getParameter(1)) | (p.getParameter(2) << 8);
		}
		else {
			return -1;
		}
	}
	return -2;
}

int XL330::getJointSpeed(int id) {
	int speed = RXsendPacket(id, XL_PRESENT_VELOCITY);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
	return speed;
}

int XL330::getJointTemperature(int id) {
	int temp = RXsendPacket(id, XL_PRESENT_TEMPERATURE);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
	return temp;
}

int XL330::isJointMoving(int id) {
	int motion = RXsendPacket(id, XL_MOVING);
	this->stream->flush();
	nDelay(NANO_TIME_DELAY);
	return motion;
}

int XL330::sendPacket(int id, int Address, int value) {
	/*Dynamixel 2.0 communication protocol
	  used by Dynamixel XL-320 and Dynamixel PRO only.
	*/
	// For sending 2-byte data
	const int bufsize = 16;

	byte txbuffer[bufsize];

	Packet p(txbuffer, bufsize, id, 0x03, 4,
		DXL_0BYTE(Address),
		DXL_1BYTE(Address),
		DXL_0BYTE(value),
		DXL_1BYTE(value));

	int size = p.getSize();
	stream->write(txbuffer, size);
	return bufsize;
}

int XL330::sendPacket_4bytes(int id, int Address, int value) {
	/*Dynamixel 2.0 communication protocol
	  used by Dynamixel XL-330 and Dynamixel PRO only.
	*/
	// For sending 4-byte data
	const int bufsize = 18;

	byte txbuffer[bufsize];

	Packet p(txbuffer, bufsize, id, 0x03, 6,
		DXL_0BYTE(Address),
		DXL_1BYTE(Address),
		DXL_0BYTE(value),
		DXL_1BYTE(value),
		DXL_2BYTE(value),
		DXL_3BYTE(value));

	int size = p.getSize();
	stream->write(txbuffer, size);
	return bufsize;
}

int XL330::sendPacket_1byte(int id, int Address, int value) {
	/*Dynamixel 2.0 communication protocol
	  used by Dynamixel XL-330 and Dynamixel PRO only.
	*/
	// For sending 1 byte data
	const int bufsize = 18;

	byte txbuffer[bufsize];

	Packet p(txbuffer, bufsize, id, 0x03, 3,
		DXL_0BYTE(Address),
		DXL_1BYTE(Address),
		DXL_0BYTE(value));

	int size = p.getSize();
	stream->write(txbuffer, size);
	return bufsize;
}


void XL330::nDelay(uint32_t nTime) {
	/*
	uint32_t max;
	for( max=0; max < nTime; max++){

	}
	*/
}

int XL330::flush() {
	this->stream->flush();
}

int XL330::RXsendPacket(int id, int Address) {
	return this->RXsendPacket(id, Address, 2);
}

int XL330::RXsendPacket(int id, int Address, int size) {

	/*Dynamixel 2.0 communication protocol
	  used by Dynamixel XL-320 and Dynamixel PRO only.
	*/

	const int bufsize = 16;

	byte txbuffer[bufsize];

	Packet p(txbuffer, bufsize, id, 0x02, 4,
		DXL_0BYTE(Address),
		DXL_1BYTE(Address),
		DXL_0BYTE(size),
		DXL_1BYTE(size));


	stream->write(txbuffer, p.getSize());

	//stream->write(txbuffer,bufsize);

	return p.getSize();
}

// from http://stackoverflow.com/a/133363/195061

#define FSM
#define STATE(x)        s_##x : if(!stream->readBytes(&BUFFER[I++],1)) goto sx_timeout ; if(I>=SIZE) goto sx_overflow; sn_##x :
#define THISBYTE        (BUFFER[I-1])
#define NEXTSTATE(x)    goto s_##x
#define NEXTSTATE_NR(x) goto sn_##x
#define OVERFLOW        sx_overflow :
#define TIMEOUT         sx_timeout :

int XL330::readPacket(unsigned char* BUFFER, size_t SIZE) {
	int C;
	int I = 0;

	int length = 0;

	// state names normally name the last parsed symbol


	FSM{
	  STATE(start) {
	if (THISBYTE == 0xFF) NEXTSTATE(header_ff_1);
	I = 0; NEXTSTATE(start);
	  }
	  STATE(header_ff_1) {
	if (THISBYTE == 0xFF) NEXTSTATE(header_ff_2);
	I = 0; NEXTSTATE(start);
	  }
	  STATE(header_ff_2) {
	if (THISBYTE == 0xFD) NEXTSTATE(header_fd);
	// yet more 0xFF's? stay in this state
	if (THISBYTE == 0xFF) NEXTSTATE(header_ff_2);
	// anything else? restart
	I = 0; NEXTSTATE(start);
	  }
	  STATE(header_fd) {
		  // reading reserved, could be anything in theory, normally 0
		  }
		  STATE(header_reserved) {
			  // id = THISBYTE
			  }
			  STATE(id) {
			length = THISBYTE;
			  }
			  STATE(length_1) {
			length += THISBYTE << 8; // eg: length=4
			  }
			  STATE(length_2) {
			  }
			  STATE(instr) {
				  // instr = THISBYTE
					  // check length because
					  // action and reboot commands have no parameters
				  if (I - length >= 5) NEXTSTATE(checksum_1);
					}
					STATE(params) {
						// check length and maybe skip to checksum
						if (I - length >= 5) NEXTSTATE(checksum_1);
						// or keep reading params
						NEXTSTATE(params);
						}
						STATE(checksum_1) {
						}
						STATE(checksum_2) {
							// done
							return I;
							}
							OVERFLOW {
								return -1;
							}
							TIMEOUT {
							return -2;
							}

	}
}


XL330::Packet::Packet(
	unsigned char* data,
	size_t data_size,
	unsigned char id,
	unsigned char instruction,
	int parameter_data_size,
	...) {


	// [ff][ff][fd][00][id][len1][len2] { [instr][params(parameter_data_size)][crc1][crc2] }
	unsigned int length = 3 + parameter_data_size;
	if (!data) {
		// [ff][ff][fd][00][id][len1][len2] { [data(length)] }
		this->data_size = 7 + length;
		this->data = (unsigned char*)malloc(data_size);
		this->freeData = true;
	}
	else {
		this->data = data;
		this->data_size = data_size;
		this->freeData = false;
	}
	this->data[0] = 0xFF;
	this->data[1] = 0xFF;
	this->data[2] = 0xFD;
	this->data[3] = 0x00;
	this->data[4] = id;
	this->data[5] = length & 0xff;
	this->data[6] = (length >> 8) & 0xff;
	this->data[7] = instruction;
	va_list args;
	va_start(args, parameter_data_size);
	for (int i = 0; i < parameter_data_size; i++) {
		unsigned char arg = va_arg(args, int);
		this->data[8 + i] = arg;
	}
	unsigned short crc = update_crc(0, this->data, this->getSize() - 2);
	this->data[8 + parameter_data_size] = crc & 0xff;
	this->data[9 + parameter_data_size] = (crc >> 8) & 0xff;
	va_end(args);
}

XL330::Packet::Packet(unsigned char* data, size_t size) {
	this->data = data;
	this->data_size = size;
	this->freeData = false;
}


XL330::Packet::~Packet() {
	if (this->freeData == true) {
		free(this->data);
	}
}

void XL330::Packet::toStream(Stream& stream) {
	stream.print("id: ");
	stream.println(this->getId(), DEC);
	stream.print("length: ");
	stream.println(this->getLength(), DEC);
	stream.print("instruction: ");
	stream.println(this->getInstruction(), HEX);
	stream.print("parameter count: ");
	stream.println(this->getParameterCount(), DEC);
	for (int i = 0; i < this->getParameterCount(); i++) {
		stream.print(this->getParameter(i), HEX);
		if (i < this->getParameterCount() - 1) {
			stream.print(",");
		}
	}
	stream.println();
	stream.print("valid: ");
	stream.println(this->isValid() ? "yes" : "no");
}

unsigned char XL330::Packet::getId() {
	return data[4];
}

int XL330::Packet::getLength() {
	return data[5] + ((data[6] & 0xff) << 8);
}

int XL330::Packet::getSize() {
	return getLength() + 7;
}

int XL330::Packet::getParameterCount() {
	return getLength() - 3;
}

unsigned char XL330::Packet::getInstruction() {
	return data[7];
}

unsigned char XL330::Packet::getParameter(int n) {
	return data[8 + n];
}

bool XL330::Packet::isValid() {
	int length = getLength();
	unsigned short storedChecksum = data[length + 5] + (data[length + 6] << 8);
	return storedChecksum == update_crc(0, data, length + 5);
}
