/*
 * Flash.c
 *
 *  Created on: 29/04/2017
 *      Author: root
 */

#include "Definitions.h"
#include "util.h"

void flash_Erase(long int addr){

	int byte0, byte1, byte2;

	byte0 = addr & 0x0000FF;
	byte1 = (addr & 0x00FF00)>>8;
	byte2 = (addr & 0xFF0000)>>16;

	while(((FTFA->FSTAT)&CCIEMask)==0x00);

	if(!((FTFA->FSTAT)==CCIEMask)){
		FTFA->FSTAT = ClearErrors;
	}

	FTFA->FCCOB0 = EraseFlash;
	FTFA->FCCOB1 = byte2;
	FTFA->FCCOB2 = byte1;
	FTFA->FCCOB3 = byte0;

	FTFA->FSTAT = CCIEMask;

	while(((FTFA->FSTAT)& CCIEMask)==0x00);
}

void flash_WriteLong(long int addr, long int value){

	int addr0, addr1, addr2;
	int value0, value1, value2, value3;

	addr0 = addr & 0x0000FF;
	addr1 = (addr & 0x00FF00)>>8;
	addr2 = (addr & 0xFF0000)>>16;

	value0 = value & 0x000000FF;
	value1 = (value & 0x0000FF00)>>8;
	value2 = (value & 0x00FF0000)>>16;
	value3 = (value & 0xFF000000)>>24;

	while(((FTFA->FSTAT)& CCIEMask )==0x00);

	if(!((FTFA->FSTAT) == CCIEMask)){
		FTFA->FSTAT = ClearErrors;
	}

	FTFA->FCCOB0 = WriteLong;

	FTFA->FCCOB1 = addr2;
	FTFA->FCCOB2 = addr1;
	FTFA->FCCOB3 = addr0;
	FTFA->FCCOB4 = value3;
	FTFA->FCCOB5 = value2;
	FTFA->FCCOB6 = value1;
	FTFA->FCCOB7 = value0;

	FTFA->FSTAT = CCIEMask;

	while((FTFA->FSTAT & CCIEMask) == 0x00);

}

void flash_write(long int addr, long int value){

	util_genDelay10ms();
	flash_Erase(addr);
	util_genDelay1ms();

//	long long int  value_aux = (long long int) value;
//	long int value_low = (long int) value_aux & 0x00000000FFFFFFFF;
//	long int value_hi = (long int) (value_aux & 0xFFFFFFFF00000000) >> 32;
//
//	flash_WriteLong(addr, value_low);
//	flash_WriteLong(addr+4, value_hi);

	flash_WriteLong(addr, value);

}

