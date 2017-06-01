/*
 * Serial.h
 *
 *  Created on: 18/10/2016
 *      Author: root
 */

#ifndef SOURCES_INTERFACE_SERIAL_H_
#define SOURCES_INTERFACE_SERIAL_H_


#define BUFF_SIZE	256U

int iTP = 0, iFP = 0;
int iTI = 0, iFI = 0;
int iTF = 0, iFF = 0;
unsigned char ucStart = 0;

typedef struct estrutura_pontos{
	int indice;
	double tempo;
	double frequencia;
	int valor;
}Ponto;

/* ***************************************************/
/* Method name:        setConfig                     */
/* Method description:  This method initialize the   */
/* 						communication           	 */
/* Input params:       n/a                           */
/* Output params:       n/a                          */
/* ***************************************************/
void serial_init(void);

/* ********************************************************/
/* Method name:        sendBuffer                         */
/* Method description:  This method sends a string through*/
/* 						the serial port	                  */
/* Input params:       *cmd = vector to be written        */
/* Output params:       n/a                               */
/* ********************************************************/
void sendBuffer(char *str);


char readBuffer(char *cmd);

void serial_SendAllPoint(Ponto *ponto, int num);

void serial_SendPoint(Ponto ponto);

void serial_GetCmd (char *cmd);

#endif /* SOURCES_INTERFACE_SERIAL_H_ */
