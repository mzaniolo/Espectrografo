#include "Serial.h"
#include "debugUart.h"
#include "fsl_debug_console.h"
#include "Definitions.h"
#include "MKL25Z4_extension.h"
#include "fsl_interrupt_manager.h"
#include <stdio.h>

char cmd[BUFF_SIZE];
unsigned char count = 0;

/******* TESTE ******/
//int iTP = 0, iFP = 0;
//int iTI = 0, iFI = 0;
//int iTF = 0, iFF = 0;
/******* TESTE ******/

/* ***************************************************/
/* Method name:        setConfig                     */
/* Method description:  This method initialize the   */
/* 						communication           	 */
/* Input params:       n/a                           */
/* Output params:       n/a                          */
/* ***************************************************/
void serial_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);
	debugUart_init();

	NVIC_ClearPendingIRQ(UART0_IRQn);

	NVIC_EnableIRQ(UART0_IRQn);
}

/* ********************************************************/
/* Method name:        sendBuffer                         */
/* Method description:  This method sends a string through*/
/* 						the serial port	                  */
/* Input params:       *cmd = vector to be written        */
/* Output params:       n/a                               */
/* ********************************************************/
void sendBuffer(char *str){

	for (int i = 0; i< BUFF_SIZE; i++)
	{

		if (0x0A != str[i] )
		{
			PUTCHAR(str[i]);
		} else
		{
			PUTCHAR(str[i]);
			break;
		}

	}

}

/* *****************************************************************/
/* Method name:        sendBuffer                                  */
/* Method description:  This method reads a byte through           */
/* 						the serial port	                           */
/* Input params:       *cmd = char to be written                   */
/* Output params:       1 if it reads something and 0 if otherwise */
/* *****************************************************************/
char readBuffer(char *cmd){

    if(UART0_BRD_S1_RDRF(UART0)){
    	*cmd = GETCHAR();
        return 1;
    }
    return 0;

}

void serial_SendPoint(Ponto ponto){

	char str[18];
	sprintf(str, "%d|%lf|%lf|%lf\n\r", ponto.indice, ponto.tempo, ponto.frequencia, ponto.valor);
	sendBuffer(str);
}

void serial_GetCmd (char *cmd){
	for (int i = 0; i<BUFF_SIZE;i++){
		while (readBuffer(cmd[i]) == 0); //espera chegar cmd
		if (cmd[i] == '\n' || cmd[i] == '\r') break;
	}
}

void serial_ParseCommand(char *cmd){

	int aux;

	if((cmd[0] == 'C' || cmd[0] == 'c') && (cmd[1] == '\n' || cmd[1] == '\r')){
		ucStart = 1U;
	}else if((cmd[0] == 'P' || cmd[0] == 'p') && (cmd[1] == '\n' || cmd[1] == '\r')){
		ucStart = 0U;
	}

	sscanf(&cmd[2], "%d\r", &aux);
	switch(cmd[1]){
	case 'i':
	case 'I':
		if (cmd[0] == 'T' || cmd[0] == 't'){
			iTI = aux;
		} else if (cmd[0] == 'F' || cmd[0] == 'f'){
			iFI = aux;
		} else {
			//retornar cmd invalido
		}
		break;
	case 'p':
	case 'P':
		if (cmd[0] == 'T' || cmd[0] == 't'){
			iTP = aux;
		} else if (cmd[0] == 'F' || cmd[0] == 'f'){
			iFP = aux;
		} else {
			//retornar cmd invalido
		}
		break;
	case 'f':
	case 'F':
		if (cmd[0] == 'T' || cmd[0] == 't'){
			iTF = aux;
		} else if (cmd[0] == 'F' || cmd[0] == 'f'){
			iFF = aux;
		} else {
			//retornar cmd invalido
		}
		break;

	}

}
void UART0_IRQHandler (void){
	cmd[count] = GETCHAR();
	if ((cmd[count] == '\n' || cmd[count] == '\r') && count == 0){
		count = 0;
	}else if (cmd[count] == '\n' || cmd[count] == '\r'){
		count = 0;
		serial_ParseCommand(cmd);
	}else count++;
}

