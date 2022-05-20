/*
 * dxl_pro.h
 * Original Code Created on: 2013. 4. 25. by ROBOTIS,.LTD.
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

#ifndef DXL_PRO_H_
#define DXL_PRO_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MAXNUM_TXPACKET     (255)//(65535)
#define MAXNUM_RXPACKET     (255)//(65535)

///////////////// utility for value ///////////////////////////
#define DXL_MAKEWORD(a, b)      ((unsigned short)(((unsigned char)(((unsigned long)(a)) & 0xff)) | ((unsigned short)((unsigned char)(((unsigned long)(b)) & 0xff))) << 8))
#define DXL_MAKEDWORD(a, b)     ((unsigned int)(((unsigned short)(((unsigned long)(a)) & 0xffff)) | ((unsigned int)((unsigned short)(((unsigned long)(b)) & 0xffff))) << 16))
#define DXL_LOWORD(l)           ((unsigned short)(((unsigned long)(l)) & 0xffff))
#define DXL_HIWORD(l)           ((unsigned short)((((unsigned long)(l)) >> 16) & 0xffff))
//#define DXL_LOBYTE(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))
//#define DXL_HIBYTE(w)           ((unsigned char)((((unsigned long)(w)) >> 8) & 0xff))
#define DXL_0BYTE(m)           ((unsigned char)(((unsigned long)(m)) & 0xff))
#define DXL_1BYTE(m)           ((unsigned char)((((unsigned long)(m)) >> 8) & 0xff))
#define DXL_2BYTE(m)           ((unsigned char)((((unsigned long)(m)) >> 16) & 0xff))
#define DXL_3BYTE(m)           ((unsigned char)((((unsigned long)(m)) >> 24) & 0xff))


#define RX_TIMEOUT_COUNT2		(1600L) //(1000L) //porting
#define NANO_TIME_DELAY			(12000) //ydh added 20111228 -> 20120210 edited ydh
#define RX_TIMEOUT_COUNT1  		(RX_TIMEOUT_COUNT2*128L)

unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);

#ifdef __cplusplus
}
#endif



#endif /* DXL_PRO_H_ */
