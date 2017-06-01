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

/*                 Flash Definitions                  */
#define CCIEMask					1UL << 7
#define ClearErrors					0x30
#define EraseFlash					0x09
#define WriteLong					0x06
/*                END OF Flash Defintions             */

#define B0_PIN                     0U                           /* Pino bobina 0 */
#define B0_OUTPUT              (GPIO_OUTPUT << B0_PIN)
#define B0_ALT 						0x01u 						/* GPIO alternative */

#define B1_PIN                     1U                           /* Pino bobina 1 */
#define B1_OUTPUT              (GPIO_OUTPUT << B1_PIN)
#define B1_ALT 						0x01u 						/* GPIO alternative */

#define B2_PIN                     2U                           /* Pino bobina 2 */
#define B2_OUTPUT              (GPIO_OUTPUT << B2_PIN)
#define B2_ALT 						0x01u 						/* GPIO alternative */

#define B3_PIN                     3U                           /* Pino bobina 3 */
#define B3_OUTPUT              (GPIO_OUTPUT << B3_PIN)
#define B3_ALT 						0x01u 						/* GPIO alternative */

#endif /* SOURCES_DEFINITIONS_H_ */
