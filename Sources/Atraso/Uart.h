/*
 * Uart.h
 *
 *  Created on: 22/10/2016
 *      Author: root
 */

#ifndef SOURCES_ATRASO_UART_H_
#define SOURCES_ATRASO_UART_H_

#define SIZE	256

void uart1_init(int baud_rate);
void uart1_write(char *cmd);
char uart1_read(char *cmd);

#endif /* SOURCES_ATRASO_UART_H_ */
