/*
 * Definitions.h
 *
 *  Created on: 18/10/2016
 *      Author: root
 */

#ifndef SOURCES_DEFINITIONS_H_
#define SOURCES_DEFINITIONS_H_

/* system includes */
#include <MKL25Z4.h>

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U


/*                 END OF General uC definitions         */

#define TRUE						1
#define FALSE						0

//#define PIT_IRQn					22U




/*                    ADC Definitions              */
#define CHANNEL						0U
#define ADC_ADICLK 					1U
#define ADC_ADCMODE 				3U
#define ADC_ADLSMP					0U
#define ADC_ADIV  					0U
#define ADC_ADLPC					0U
#define ADC_REFSEL					0U
#define ADC_DMAEN					0U
#define ADC_ACFE					0U
#define ADC_ADTRG					0U
#define ADC_ADLSTS					0U
#define ADC_ADHSC           		0U
#define ADC_ADACKEN					0U
#define ADC_MUXSEL					0U
/*                 END OF ADC definitions             */

#endif /* SOURCES_DEFINITIONS_H_ */
