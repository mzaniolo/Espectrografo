/*
 * Motor.h
 *
 *  Created on: 21/10/2016
 *      Author: root
 */

#ifndef SOURCES_ATRASO_MOTOR_H_
#define SOURCES_ATRASO_MOTOR_H_

typedef enum Error_Codes {None, OutOfRange}Error;

#define LIM_SUP 	75
#define LIM_INF		-75

void motor_init();

void home ();

Error mv_absolute(double pos);

Error mv_relative (double pos);

void stop ();

double getPosicao();

#endif /* SOURCES_ATRASO_MOTOR_H_ */
