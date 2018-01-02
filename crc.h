
#ifndef __CRC_H__
#define __CRC_H__

#include "stdio.h"
#include "stdint.h" 

#define True	1	
#define False	0

typedef enum
{
	crc4_ITU			= 0,	//x4+x+1;		Poly:0x03; Init:0x00; Refin:True; Refout:True; Xorout:0x00;
	crc5_EPC			= 1,	//x5+x3+1;		Poly:0x09; Init:0x09; Refin:False; Refout:False; Xorout:0x00;
	crc5_ITU			= 2,	//x5+x4+x2+1;	Poly:0x15; Init:0x00; Refin:True; Refout:True; Xorout:0x00;
	crc5_USB			= 3,	//x5+x2+1;		Poly:0x05; Init:0x1F; Refin:True; Refout:True; Xorout:0x1F;
	crc6_ITU			= 4,	//x6+x+1;		Poly:0x03; Init:0x00; Refin:True; Refout:True; Xorout:0x00;
	crc7_MMC			= 5,	//x7+x3+1;		Poly:0x09; Init:0x00; Refin:False; Refout:False; Xorout:0x00;
	crc8				= 6,	//x8+x2+x+1;	Poly:0x07; Init:0x00; Refin:False; Refout:False; Xorout:0x00;
	crc8_ITU			= 7,	//x8+x2+x+1;	Poly:0x07; Init:0x00; Refin:False; Refout:False; Xorout:0x55;
	crc8_ROHC			= 8,	//x8+x2+x+1;	Poly:0x07; Init:0xFF; Refin:True; Refout:True; Xorout:0x00;
	crc8_MAXIM			= 9,	//x8+x5+x4+1;	Poly:0x31; Init:0x00; Refin:True; Refout:True; Xorout:0x00;
	crc16_IBM			= 10,	//x16+x15+x2+1;	Poly:0x8005; Init:0x0000; Refin:True; Refout:True; Xorout:0x0000;
	crc16_MAXIM			= 11,	//x16+x15+x2+1;	Poly:0x8005; Init:0x0000; Refin:True; Refout:True; Xorout:0xFFFF;
	crc16_USB			= 12,	//x16+x15+x2+1;	Poly:0x8005; Init:0xFFFF; Refin:True; Refout:True; Xorout:0xFFFF;
	crc16_MODBUS		= 13,	//x16+x15+x2+1;	Poly:0x8005; Init:0xFFFF; Refin:True; Refout:True; Xorout:0x0000;
	crc16_CCITT			= 14,	//x16+x12+x5+1;	Poly:0x1021; Init:0x0000; Refin:True; Refout:True; Xorout:0x0000;
	crc16_CCITT_FALSE	= 15,	//x16+x12+x5+1;	Poly:0x1021; Init:0xFFFF; Refin:False; Refout:False; Xorout:0x0000;
	crc16_X25			= 16,	//x16+x12+x5+1;	Poly:0x1021; Init:0xFFFF; Refin:True; Refout:True; Xorout:0xFFFF;
	crc16_XMODEM		= 17,	//x16+x12+x5+1;	Poly:0x1021; Init:0x0000; Refin:False; Refout:False; Xorout:0x0000;
	crc16_DNP			= 18,	//x16+x13+x12+x11+x10+x8+x6+x5+x2+1;	Poly:0x3D65; Init:0x0000; Refin:True; Refout:True; Xorout:0xFFFF;
	crc32				= 19,	//x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1;	Poly:0x4C11DB7; Init:0xFFFFFFF; Refin:True; Refout:True; Xorout:0xFFFFFFF;
	crc32_MPEG_2		= 20,	//x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1;	Poly:0x4C11DB7; Init:0xFFFFFFF; Refin:False; Refout:False; Xorout:0x0000000;

}CRC_Name;

void crc_InitTable(CRC_Name PolyName);
uint8_t crc8Bits_InitTable(uint8_t PolyValue,uint8_t InitValue,uint8_t ReflectStatus,uint8_t XorOutValue);
uint8_t crc16Bits_InitTable(uint16_t PolyValue,uint16_t InitValue,uint8_t IsReflected,uint16_t XorOutValue);
uint8_t crc32Bits_InitTable(uint32_t PolyValue,uint32_t InitValue,uint8_t IsReflected,uint32_t XorOutValue);


#endif
