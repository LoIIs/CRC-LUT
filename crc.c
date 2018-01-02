
#include "crc.h"

static uint8_t crc8_Table[256];
static uint16_t crc16_Table[256];
static uint32_t crc32_Table[256];

void crc_InitTable(CRC_Name PolyName)
{
	uint8_t i,crc; 
    uint16_t dividend,crc16;

	switch(PolyName)
	{
		case 0:		//crc4_ITU
			crc = 0;
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for (i = 0; i < 8; ++i)  
		        {  
		            if (crc & 1)  
		                crc = (crc >> 1) ^ 0x0C;// 0x0C = (reverse 0x03)>>(8-4)  
		            else  
		                crc = (crc >> 1);  
		        }  
		        crc8_Table[dividend] = crc;
		    }
		break;
		case 1:		//crc5_EPC
			crc = 0x48; // Initial value: 0x48 = 0x09<<(8-5)
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for ( i = 0; i < 8; i++ )  
		        {  
		            if ( crc & 0x80 )  
		                crc = (crc << 1) ^ 0x48;  // 0x48 = 0x09<<(8-5)  
		            else  
		                crc <<= 1;  
		        }  
		        crc8_Table[dividend] = crc>>3;
		    }
		break;
		case 2:		//crc5_ITU
			crc = 0;        // Initial value
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for (i = 0; i < 8; ++i)  
		        {  
		            if (crc & 1)  
		                crc = (crc >> 1) ^ 0x15;// 0x15 = (reverse 0x15)>>(8-5)  
		            else  
		                crc = (crc >> 1);  
		        }  
		        crc8_Table[dividend] = crc;
		    }
		break;
		case 3:		//crc5_USB
			crc = 0x1F;     // Initial value
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for (i = 0; i < 8; ++i)  
		        {  
		            if (crc & 1)  
		                crc = (crc >> 1) ^ 0x14;// 0x14 = (reverse 0x05)>>(8-5)  
		            else  
		                crc = (crc >> 1);  
		        }  
		        crc8_Table[dividend] = crc^0x1F;
		    }
		break;
		case 4:		//crc6_ITU
			crc = 0;    // Initial value  
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for (i = 0; i < 8; ++i)  
		        {  
		            if (crc & 1)  
		                crc = (crc >> 1) ^ 0x30;// 0x30 = (reverse 0x03)>>(8-6)  
		            else  
		                crc = (crc >> 1);  
		        }  
		        crc8_Table[dividend] = crc;
		    }
		break;
		case 5:		//crc7_MMC
			crc = 0;    // Initial value  
			for(dividend=0;dividend<256;dividend++)
		    {  
		        crc ^= dividend;     // crc ^= *data; data++;  
		        for ( i = 0; i < 8; i++ )  
		        {  
		            if ( crc & 0x80 )  
		                crc = (crc << 1) ^ 0x12;  // 0x12 = 0x09<<(8-7)  
		            else  
		                crc <<= 1;  
		        }  
		        crc8_Table[dividend] = crc>>1;
		    }
		break;
		case 6:		//crc8
			crc8Bits_InitTable(0x07,0x00,False,0x00);
		break;
		case 7:		//crc8_ITU
			crc8Bits_InitTable(0x07,0x00,False,0x55);
		break;
		case 8:		//crc8_ROHC
			crc8Bits_InitTable(0x07,0xFF,True,0x00);
		break;
		case 9:		//crc8_MAXIM
			crc8Bits_InitTable(0x31,0x00,True,0x00);
		break;
		case 10:	//crc16_IBM
			crc16Bits_InitTable(0x8005,0x0000,True,0x0000);
		break;
		case 11:	//crc16_MAXIM
			crc16Bits_InitTable(0x8005,0x0000,True,0xFFFF);
		break;
		case 12:	//crc16_USB
			crc16Bits_InitTable(0x8005,0xFFFF,True,0xFFFF);
		break;
		case 13:	//crc16_MODBUS
			crc16Bits_InitTable(0x8005,0xFFFF,True,0x0000);
		break;
		case 14:	//crc16_CCITT
			crc16Bits_InitTable(0x1021,0x0000,True,0x0000);
		break;
		case 15:	//crc16_CCITT_FALSE
			crc16Bits_InitTable(0x1021,0xFFFF,False,0x0000);
		break;
		case 16:	//crc16_X25
			crc16Bits_InitTable(0x1021,0xFFFF,True,0xFFFF);
		break;
		case 17:	//crc16_XMODEM
			crc16Bits_InitTable(0x1021,0x0000,False,0x0000);
		break;
		case 18:	//crc16_DNP
			crc16Bits_InitTable(0x3D65,0x0000,True,0xFFFF);
		break;
		case 19:	//crc32
			crc32Bits_InitTable(0x04C11DB7,0xFFFFFFFF,True,0xFFFFFFFF);
		break;
		case 20:	//crc32_MPEG_2
			crc32Bits_InitTable(0x04C11DB7,0xFFFFFFFF,False,0x00000000);
		break;
		default:
		break;
	}
}

uint8_t reverse_8Bits(uint8_t data)
{
    uint8_t i,value=0;
    for (i = 0; i < 8; ++i)
    {
    	value <<= 1;
        value |= (data&0x01);       
        data >>= 1; 
    }
    return value;
}

uint16_t reverse_16Bits(uint16_t data)
{
    uint8_t i;
    uint16_t value=0;
    for (i = 0; i < 16; ++i)
    {
    	value <<= 1;
        value |= (data&0x0001);   
        data >>= 1; 
    }
    return value;
}

uint32_t reverse_32Bits(uint32_t data)
{
    uint8_t i;
    uint32_t value=0;
    for (i = 0; i < 32; ++i)
    {
    	value <<= 1;
        value |= (data&0x00000001);
        data >>= 1; 
    }
    return value;
}


/****************************************************************************** 
 * PolyValue:    多项式特征值 
 * InitValue:    CRC初始值 
 * IsReflected:  是否反转,True:反转 LSF;False: 不反转 MSF
 * XorOutValue:  异或值
 * Note: 
 *****************************************************************************/  
uint8_t crc8Bits_InitTable(uint8_t PolyValue,uint8_t InitValue,uint8_t IsReflected,uint8_t XorOutValue)
{
    uint8_t bit;
    uint16_t dividend;
    uint8_t crcValue,Polynomial;
    
    crcValue = InitValue; 
    if (IsReflected==False)
    {
        Polynomial = PolyValue;
    }
    else if (IsReflected==True)
    {
        Polynomial = reverse_8Bits(PolyValue);
    }
    else
        return 0;
    for(dividend=0;dividend<256;dividend++)
    {    
        /* Try to divide the current data bit.  */ 
        if (IsReflected==False)
         {
            crcValue ^= dividend; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {                   
                if (crcValue & 0x80)  
                crcValue = (crcValue << 1) ^ Polynomial;  
                else  
                crcValue = crcValue << 1;
            }
         } 
         else if(IsReflected==True)
         {
            crcValue ^= dividend; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {
                if(crcValue & 1)
                    crcValue = (crcValue >> 1) ^ Polynomial;
                else
                    crcValue = crcValue >> 1;
            }
         }
         else
            return 0;                    
        /* Save the result in the table. */  
        crc8_Table[dividend] = crcValue ^ XorOutValue; 
    }
    return 1;
}

uint8_t crc16Bits_InitTable(uint16_t PolyValue,uint16_t InitValue,uint8_t IsReflected,uint16_t XorOutValue)
{
    uint8_t bit;
    uint16_t dividend;
    uint16_t crcValue,Polynomial;
    
    crcValue = InitValue; 
    if (IsReflected==False)
    {
        Polynomial = PolyValue;
    }
    else if (IsReflected==True)
    {
        Polynomial = reverse_16Bits(PolyValue);
    }
    else
        return 0;
    for(dividend=0;dividend<256;dividend++)
    {    
        /* Try to divide the current data bit.  */ 
        if (IsReflected==False)
         {
            crcValue ^= (uint16_t)dividend<<8; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {                   
                if (crcValue & 0x8000)  
                crcValue = (crcValue << 1) ^ Polynomial;  
                else  
                crcValue = crcValue << 1;
            }
         } 
         else if(IsReflected==True)
         {
            crcValue ^= dividend; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {
                if(crcValue & 1)
                    crcValue = (crcValue >> 1) ^ Polynomial;
                else
                    crcValue = crcValue >> 1;
            }
         }
         else
            return 0;                    
        /* Save the result in the table. */  
        crc16_Table[dividend] = crcValue ^ XorOutValue; 
    }
    return 1;
}

uint8_t crc32Bits_InitTable(uint32_t PolyValue,uint32_t InitValue,uint8_t IsReflected,uint32_t XorOutValue)
{
    uint8_t bit;
    uint16_t dividend;
    uint32_t crcValue,Polynomial;
    
    crcValue = InitValue; 
    if (IsReflected==False)
    {
        Polynomial = PolyValue;
    }
    else if (IsReflected==True)
    {
        Polynomial = reverse_32Bits(PolyValue);
    }
    else
        return 0;
    for(dividend=0;dividend<256;dividend++)
    {    
        /* Try to divide the current data bit.  */ 
        if (IsReflected==False)
         {
            crcValue ^= (uint32_t)dividend<<24; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {                   
                if (crcValue & 0x80000000)  
                	crcValue = (crcValue << 1) ^ Polynomial;  
                else  
                	crcValue = crcValue << 1;
            }
         } 
         else if(IsReflected==True)
         {
            crcValue ^= dividend; 
            /* Shift and XOR with the polynomial.   */  
            for(bit = 0; bit < 8; bit++)  
            {
                if(crcValue & 1)
                    crcValue = (crcValue >> 1) ^ Polynomial;
                else
                    crcValue = crcValue >> 1;
            }
         }
         else
            return 0;                    
        /* Save the result in the table. */  
        crc32_Table[dividend] = crcValue ^ XorOutValue; 
    }
    return 1;
}

