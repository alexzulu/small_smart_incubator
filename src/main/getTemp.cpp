/*
 * getTemp.cpp
 *
 *  Created on: 11 февр. 2019 г.
 *      Author: alex
 */

#include "main.h"

extern float g_oldTemperature;
extern float g_realTemperature;
extern float g_DHTHumidity;
extern bool g_heaterState;
extern float lastTime;
extern float lastRealTemperature;
extern LiquidCrystal_I2C lcd;
extern DallasTemperature sensors;
extern DeviceAddress TL0;
extern DHT dht;

float getTemp() {
	float celsius;
	sensors.requestTemperatures();
	celsius = sensors.getTempC(TL0);
	return celsius;
}

float getDHTTemperature() {
	float celsius;
	celsius = dht.readTemperature();
	return celsius;
}

float getDHTHumidity() {
	float humidity;
	humidity = dht.readHumidity();
	return humidity;
}

void printSetupTempLCD() {
	lcd.setCursor(0, 0);
	lcd.print("S:");
	lcd.setCursor(2, 0);
	lcd.print("     ");
	lcd.setCursor(2, 0);
	lcd.print(setTemperature);
}

void printTempLCD() {
	float current = g_realTemperature;
	if (g_oldTemperature != current) {
		lcd.setCursor(2, 1);
		lcd.print("     ");
		lcd.setCursor(2, 1);
		lcd.print(current);
		g_oldTemperature = current;
	}
}

void printHumidityLCD() {
	lcd.setCursor(11, 1);
	lcd.print("     ");
	lcd.setCursor(11, 1);
	lcd.print(g_DHTHumidity);
}

void printHeaterStateLCD() {
	lcd.setCursor(15, 0);
	lcd.print(g_heaterState);
}

void heaterControl() {
	if (g_realTemperature < setTemperature) {
		if (digitalRead(HEATER_PIN) == LOW) {
			digitalWrite(HEATER_PIN, HIGH);
			g_heaterState = 1;
		}
	}
	if (g_realTemperature >= setTemperature) {
		if (digitalRead(HEATER_PIN) == HIGH) {
			digitalWrite(HEATER_PIN, LOW);
			g_heaterState = 0;
		}
	}
}

void temperatureControl() {
	float currentTime = millis();
	if (currentTime - lastTime > controlDelay) {
		if (lastRealTemperature != g_realTemperature) {
			heaterControl();
			if (DEBUG == 1) {
				Serial.println(
						"Set: " + String(setTemperature) + "; Real: "
								+ String(g_realTemperature) + "; Hum: "
								+ String(g_DHTHumidity) + "; Relay status: "
								+ g_heaterState + ";");
			}
			lastTime = currentTime;
		}
	}
}

