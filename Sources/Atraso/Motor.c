/*
 * Motor.c
 *
 *  Created on: 21/10/2016
 *      Author: root
 */

#include "Motor.h"
#include "Uart.h"
#include "Timer.h"
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


Error motor_ReadResponse(char *str){
	motor_StartTimer();
	for (int i = 0; i<SIZE;i++){
		while (uart1_read(&str[i]) == 0 && !timeout); //espera chegar cmd
		if (timeout) return Timeout;
		if (str[i] == '\n' || str[i] == '\r') break;
	}

	return None;
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
	double posAtual;
	Error erro = getPosicao(&posAtual);

	if (erro == Timeout) return Timeout;

	double posFutura = posAtual + pos;

	if (posFutura > LIM_SUP || posFutura < LIM_INF){
		return OutOfRange;
	}

	char str[SIZE];
	sprintf(str, "1PR%f\n\r", pos); //3 casas de presisao, vai dar????

	uart1_write(str);

	return None;
}

void stop (){
	uart1_write("1ST\n\r");
}

Error getPosicao(double *pos){

	uart1_write("1TP\n\r");

	char str[20];

	if (motor_ReadResponse(str) == Timeout) return Timeout;


	sscanf(str, "1TP%lf", pos);

	return None;
}

Error WaitStop(){
	unsigned char Moving;
	char str[SIZE];
	unsigned int ControllerState = 0;

	do{
		uart1_write("1TS\n\r");
		if (motor_ReadResponse(str) == Timeout) return Timeout;

		if (str[7] > '0' && str[7] < '9'){
			ControllerState = str[7] - '0';
		}else if(str[7] > 'a' && str[7] < 'f'){
			ControllerState = str[7] - 'a' + 10;
		}else if(str[7] > 'A' && str[7] < 'F'){
			ControllerState = str[7] - 'A' + 10;
		}else return ControllerInvalidState;

		if (str[8] > '0' && str[8] < '9'){
			ControllerState += (str[8] - '0')*16;
		}else if(str[8] > 'a' && str[8] < 'f'){
			ControllerState += (str[8] - 'a' + 10)*16;
		}else if(str[8] > 'A' && str[8] < 'F'){
			ControllerState += (str[8] - 'A' + 10)*16;
		}else return ControllerInvalidState;


		switch (ControllerState){
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
			Moving = 0;
			break;
		case 0x28:
		case 0x1E:
		case 0x1F:
			Moving = 1;
			break;
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x11:
			return NotReferenced;
		case 0x3C:
		case 0x3D:
		case 0x3E:
			return CotrollerDisable;
		default:
			return ControllerInvalidState;
		}

	}while (Moving);

	return None;

}
