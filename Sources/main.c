/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/******* Includes ***********/
#include "fsl_device_registers.h"
#include "Definitions.h"
#include "Interface/Serial.h"
#include "Atraso/Motor.h"
#include "mcg_hal.h"
#include "util.h"
/****************************/
#include "Atraso/Uart.h"
#include <stdio.h>


int iTP = 0, iFP = 0;
int iTI = 0, iFI = 0;
int iTF = 0, iFF = 0;

void main_init(){
	mcg_clockInit();
	serial_init();
	motor_init();

}

/* TESTE */
void teste(){

}
/* TESTE */

int main(void){

	main_init();
	char cmd[256];
	int aux = 0;
    while(TRUE) {


    	for(int i = 0; i<256;i++){
    		while (readBuffer(&cmd[i]) == 0){}
    		if(cmd[i] == '\n' || cmd[i] == '\r') break;
    	}

    	//serial_GetCmd(cmd);
    	sscanf(&cmd[2], "%d\r", &aux);
    	switch(cmd[1]){
    	case 'i':
    	case 'I':
    		if (cmd[0] == 'T' || cmd[0] == 't'){
    			iTI = aux;
    		} else if (cmd[0] == 'F' || cmd[0] == 'f'){
    			iFI = aux;
    		} else {

    		}
    		break;
    	case 'p':
    	case 'P':
    		if (cmd[0] == 'T' || cmd[0] == 't'){
				iTP = aux;
			} else if (cmd[0] == 'F' || cmd[0] == 'f'){
				iFP = aux;
			} else {

			}
    		break;
    	case 'f':
    	case 'F':
    		if (cmd[0] == 'T' || cmd[0] == 't'){
				iTF = aux;
			} else if (cmd[0] == 'F' || cmd[0] == 'f'){
				iFF = aux;
			} else {

			}
			break;
    	case 's':
    	case 'S':
    		sendBuffer("20\n");
			for(int i = 0; i<20; i++){
				serial_SendPoint(i, cos(i));
			}
			break;

    	}
    	if (iTP != 0 && iFP != 0 && iTI != 0 && iFI != 0 && iTF != 0 && iFF != 0){

    	}

    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
