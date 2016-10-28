/*
 * Motor.c
 *
 *  Created on: 21/10/2016
 *      Author: root
 */

#include "Motor.h"
#include "Uart.h"
#include <stdio.h>


void motor_init(){
	uart1_init(9600);
}

void home (){
	uart1_write("OR\n\r");
}

Error mv_absolute(double pos) {

	if(pos > LIM_SUP || pos < LIM_INF){
		return OutOfRange;
	}

	char str[32]; //str[] = "PA";
	//snprintf(posicao, sizeof(posicao), "%g", pos);
	sprintf(str,"PA%f\n", pos); //3 casas de presisao, vai dar????
	//strcat(str, posicao);
	//strcat(str, "\n\r");
	uart1_write(str);

	return None;
}

Error mv_relative (double pos){

	//esperar parar
	double posAtual = getPosicao();

	double posFutura = posAtual + pos;

	if (posFutura > LIM_SUP || posFutura < LIM_INF){
		return OutOfRange;
	}

	char str[50];//, str[] = "PR";
	sprintf(str, "PR%f\n\r", pos); //3 casas de presisao, vai dar????
	//strcat(str, posicao);
	//strcat(str, "\n\r");
	uart1_write(str);

	return None;
}

void stop (){
	uart1_write("ST\n\r");
}

double getPosicao(){


	uart1_write("TP\n\r");

	char str[20];

	for (int i = 0; i<20;i++){
		while (uart1_read(&str[i]) == 0); //espera chegar cmd
		if (str[i] == '\n' || str[i] == '\r') break;
	}

	/** Processar a string aqui **/ //string do tipo TP10.2

	return 1.0; //mudar aqui
}
