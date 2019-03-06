/*
 * main.h
 *
 *  Created on: 11 февр. 2019 г.
 *      Author: alex
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const float setTemperature = 25.0; //Установленная температура
const bool DEBUG = 0; //Вкл/откл режим отладки
const int controlDelay = 5000; //Задержка опроса.
const int ONE_WIRE_BUS = 7; //Нога на которой работает шина
const int TEMPERATURE_PRECISION = 12; //Разрешение датчика

#define HEATER_PIN 9//Пин управления реле
#define DHT_PIN 5 //Пин датчика DHT22

#endif /* MAIN_H_ */
