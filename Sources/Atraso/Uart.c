/*
 * Uart.c
 *
 *  Created on: 22/10/2016
 *      Author: root
 */


#include "fsl_uart_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"

#define SIZE	10

void uart1_init(int baud_rate)
{
	register unsigned int sbr;
	unsigned char temp;

	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Enable the clock to UART1
	SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

	// Enable the pins of UART output
	PORTE_PCR0 |= PORT_PCR_MUX(3); // Select the function of       PTE0 to be UART1TX
	PORTE_PCR1 |= PORT_PCR_MUX(3); // Select the function of       PTE1 to be UART1RX

	UART1_C2 = 0x0;
	// Make sure that the Transmitter and Receiver is disabled
	UART1_C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	UART1_C1 = 0x0; // Set default settings

	// Calculate Baud Rate
	sbr = (unsigned int)((CLOCK_SYS_GetBusClockFreq())/(baud_rate * 16)); //     Calculate baud settings

	// Strip off the current value of the UARTx_BDH except for the SBR field
	temp = UART1_BDH & ~(UART_BDH_SBR_MASK);

	// Set Baud Rate Registers
	UART1_BDH = temp | UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	UART1_BDL = (unsigned char)(sbr & UART_BDL_SBR_MASK);

	// Enable receiver and transmitter
	UART1_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

}

void uart1_write(char *cmd){

	for(int i = 0; i<SIZE; i++){
		while((UART1_S1 & UART_S1_TDRE_MASK) == 0); //Espera esvaziar o buffer
		UART1_D = cmd[i];
		if(cmd[i] == '\n' || cmd[i] == '\r') break;
	}

}

char uart1_read(char *cmd){
	if ((UART1_S1 & UART_S1_RDRF_MASK) == 0) return 0; //se buffer vazio sai retorna 0
	cmd[0] = UART1_D;
	return 1;
}
