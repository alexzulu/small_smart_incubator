/*
 * getTemp.h
 *
 *  Created on: 11 февр. 2019 г.
 *      Author: alex
 */

#ifndef GETTEMP_H_
#define GETTEMP_H_

float getTemp ();
float getDHTTemperature();
float getDHTHumidity();
void printTempLCD();
void printHumidityLCD();
void printHeaterStateLCD();
void heaterControl();
void temperatureControl();
void printSetupTempLCD();

#endif /* GETTEMP_H_ */
