/*
 * MotorPasso.c
 *
 *  Created on: 28/05/2017
 *      Author: root
 */

#include "MotorPasso.h"
#include "util.h"
#include "Definitions.h"

void motor_passo_init(){

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	PORTB_PCR0 |= PORT_PCR_MUX(B0_ALT); //GPIO
	PORTB_PCR1 |= PORT_PCR_MUX(B1_ALT); //GPIO
	PORTB_PCR2 |= PORT_PCR_MUX(B2_ALT); //GPIO
	PORTB_PCR3 |= PORT_PCR_MUX(B3_ALT); //GPIO

	GPIOB_PDDR |= GPIO_PDDR_PDD(B0_OUTPUT | B1_OUTPUT | B2_OUTPUT | B3_OUTPUT );

}

void motor_MoverPassos(int passos, int dir){
	static unsigned char passo = 0;

	for(int i = 0; i<passos; i++){
		switch(passo){
			case 0:
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B0_PIN) ); //set 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break;  // 0001
			case 1:
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B0_PIN) ); //set 0
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B1_PIN) ); //set 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break;  // 0011
			case 2:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B1_PIN) ); //set 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break;  // 0010
			case 3:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B1_PIN) ); //set 1
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B2_PIN) ); //set 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break;  // 0110
			case 4:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B2_PIN) ); //set 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break;  // 0100
			case 5:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B2_PIN) ); //set 2
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B3_PIN) ); //set 3
				break;  // 1100
			case 6:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B3_PIN) ); //set 3
				break;  // 1000
			case 7:
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B0_PIN) ); //set 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PSOR |= GPIO_PSOR_PTSO( (0x01U << B3_PIN) ); //set 3
				break;  // 1001

			default:
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B0_PIN) ); //clear 0
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B1_PIN) ); //clear 1
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B2_PIN) ); //clear 2
				GPIOB_PCOR |= GPIO_PCOR_PTCO( (0x01U << B3_PIN) ); //clear 3
				break; // 0000
		}
		if(dir) passo++; else passo--;
		if(passo>7)passo=0;
		if(passo<0)passo=7;
		util_genDelay1ms();  // speed
		util_genDelay1ms();
	}
}
