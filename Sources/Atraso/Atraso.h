/*
 * Atraso.h
 *
 *  Created on: 04/04/2017
 *      Author: root
 */

#ifndef SOURCES_ATRASO_ATRASO_H_
#define SOURCES_ATRASO_ATRASO_H_

const double C = 0.000299792458; //[mm/fs]

void atraso_init(void);

void atraso_MoverRelativo(int Tempo);

void atraso_MoverAbsolute(int Tempo);

#endif /* SOURCES_ATRASO_ATRASO_H_ */
