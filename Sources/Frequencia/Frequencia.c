/*
 * Frequencia.c
 *
 *  Created on: 10/06/2017
 *      Author: root
 */

#include "Frequencia.h"
#include "MotorPasso.h"
#include <stdlib.h>

static double FreqAtual = 0;

void frequencia_init(){
	motor_passo_init();
}

void frequencia_MoverRelativo(double dFreq){
	int dir;
	if(dFreq>=0) dir = 1; else dir = 0;

	motor_MoverGraus(abs(dFreq)*Calib, dir);

	if(dir)
		FreqAtual += dFreq;
	else
		FreqAtual -= dFreq;
}

void frequencia_MoverAbsoluto(double dFreq){

	double DeltaFreq = (dFreq - FreqAtual);

	int dir;
	if(DeltaFreq>=0) dir = 1; else dir = 0;

	motor_MoverGraus(abs(DeltaFreq)*Calib, dir);

	FreqAtual = dFreq;
}
