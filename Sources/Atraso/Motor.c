/*
 * Motor.c
 *
 *  Created on: 21/10/2016
 *      Author: root
 */

#include "Motor.h"
#include "Uart.h"
#include <stdio.h>

volatile unsigned int timeout = 0;

void motor_init(){
	uart1_init(57600);
	timer_init(1); /* verificar unidade */
}

void motor_CommunicationTimeout(){
	timeout = 1;
}

void motor_StartTimer(){
	timeout = 0;
	timer_start();
}

void home (){
	uart1_write("1OR\n\r");
}

Error mv_absolute(double pos) {

	if(pos > LIM_SUP || pos < LIM_INF){
		return OutOfRange;
	}

	char str[32];
	sprintf(str,"1PA%f\n\r", pos); //3 casas de presisao, vai dar????
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

	char str[50];
	sprintf(str, "1PR%f\n\r", pos); //3 casas de presisao, vai dar????

	uart1_write(str);

	return None;
}

void stop (){
	uart1_write("1ST\n\r");
}

double getPosicao(){


	uart1_write("1TP\n\r");

	char str[20];

	motor_StartTimer();
	for (int i = 0; i<SIZE;i++){
		while (uart1_read(&str[i]) == 0 && !timeout); //espera chegar cmd
		if (timeout) break; /* Erro ??? */
		if (str[i] == '\n' || str[i] == '\r') break;
	}

	/** Processar a string aqui **/ //string do tipo 1TP10.2

	return 1.0; //mudar aqui
}
