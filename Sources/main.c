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
#include "Atraso/Atraso.h"
#include "Frequencia/MotorPasso.h"
#include "Detector/Detector.h"
#include "mcg_hal.h"
#include "util.h"
#include "Flash.h"
/****************************/


void main_init(){
	mcg_clockInit();
	serial_init();
	atraso_init();
	detector_Init();
	motor_passo_init();
}

int main(void){


	main_init();

	Ponto *pontos;
	int Ind;
    while(TRUE) {

		if (ucStart == 1) {
			int numPontos = (abs((iTF - iTI)/iTP) + 1) * (abs((iFF - iFI)/iFP) + 1);
			pontos = malloc(sizeof(Ponto) * numPontos);
			Ind = 0;
			for(int t = iTI; abs(t)<= abs(iTF); t += iTP){
				atraso_MoverRelativo(iTP);
				for (int f = iFI; f<=iFF; f += iFP){
					motor_MoverPassos(iFP, 1);
					pontos[Ind].valor = detector_getData();
					pontos[Ind].indice  = Ind;
					pontos[Ind].tempo = t;
					pontos[Ind].frequencia = f;
					Ind++;
				}
			}
			ucStart = 0;
			serial_SendAllPoint(pontos, Ind);
			free(pontos);
		}



    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
