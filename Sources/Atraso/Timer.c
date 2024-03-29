/*
 * Timer.c
 *
 *  Created on: 12/11/2016
 *      Author: root
 */

#include "Timer.h"
#include "Motor.h"
#include "fsl_clock_manager.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "fsl_pit_hal.h"
#include "MKL25Z4.h"
#include "fsl_interrupt_manager.h"


void timer_init(int iTempo){
	// iTempo em ms

	// PIT Initialization


	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;     // Enable the clock to the PIT module

	PIT_LDVAL0 = (unsigned int) (CLOCK_SYS_GetBusClockFreq() * iTempo)/1000;     // Default start value

	PIT_MCR = 0;	//PIT_MCR_FRZ_MASK;     // Enable clock for timer, freeze timer in debug mode

	PIT_TCTRL0 = PIT_TCTRL_TIE_MASK;     // Enable timer interrupt



	// Initialize the NVIC to enable the PIT interrupt


	NVIC_ClearPendingIRQ(PIT_IRQn);
//	NVIC->ICPR[0] = 1 << PIT_IRQn;

	NVIC_EnableIRQ(PIT_IRQn);
//	NVIC->ISER[0] = 1 << PIT_IRQn;


}

void timer_start(){
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	timeout = 0;
}


void PIT_IRQHandler(void){

	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;     // Disable timer

	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;     // Clear the timer interrupt flag

	timeout = 1;

}
