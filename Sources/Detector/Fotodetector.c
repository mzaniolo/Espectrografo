/*
 * Fotodetector.c
 *
 *  Created on: 06/03/2017
 *      Author: root
 */

/*

void ADC_Init(){
	SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);

	PORTE_PCR20 = PORT_PCR_MUX(0);

	ADC0_CFG1 |= (ADC_CFG1_ADICLK(ADC_ADICLK) | ADC_CFG1_MODE(ADC_ADCMODE) | ADC_CFG1_ADLSMP(ADC_ADLSMP) | ADC_CFG1_ADIV(ADC_ADIV) | ADC_CFG1_ADLPC(ADC_ADLPC));
}

void ADC_initConvertion(){
	ADC0_SC1A &= (ADC_SC1_ADCH(CHANNEL) | ADC_SC1_DIFF(0) | ADC_SC1_AIEN(0));

}

int ADC_isDone(){
	if(ADC0_SC1A >> 7)
		return 0;
	else
		return 1;
}

int ADC_getData(){
	sensor_initConvertion(CHANNEL);
	while(sensor_isAdcDone()){}
    return ADC0_RA; // return the register value that keeps the result of convertion
}
*/
