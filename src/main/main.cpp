/*
 * main.cpp
 *
 *  Created on: 11 февр. 2019 г.
 *      Author: alex
 */

#include <avr/wdt.h>//Подключаем библиотеку для работы с watch dog timer
#include "main.h"
#include "getTemp.h"

float g_oldTemperature; //Предыдущее замерянное значение температуры
float g_realTemperature; //Реальная температура
float g_DHTTemperature;
float g_DHTHumidity;
bool g_heaterState = 0; //Состояние нагревателя
float lastTime = 0; //Время предыдущего замера
float lastRealTemperature = 38.00; //Предыдущее значение температуры

LiquidCrystal_I2C lcd(0x27, 16, 2);
// LiquidCrystal_I2C lcd(0x3f, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress TL0 = { 0x28, 0x5B, 0xED, 0xA9, 0x06, 0x00, 0x00, 0x15 }; //Адрес датчика
DHT dht(DHT_PIN, DHT22);

void setup() {
// Инициализация пинов
	pinMode(HEATER_PIN, OUTPUT);
	digitalWrite(HEATER_PIN, LOW);

	wdt_enable(WDTO_8S); //Включаем watch dog timer и ставим период 8 секунд

	Serial.begin(115200);
	if (DEBUG != 0) {
		Serial.println("Debug mode ON");
	} else {
		Serial.println("Debug mode OFF");
	}

	sensors.begin();
	sensors.setResolution(TL0, TEMPERATURE_PRECISION); //Установка разрешения датчика

	dht.begin();

	lcd.init(); //Инициализируем lcd
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(2, 0);
	lcd.print("Small smart");
	lcd.setCursor(3, 1);
	lcd.print("incubator");
	delay(3000);
	lcd.clear();
	printSetupTempLCD();
	lcd.setCursor(0, 1);
	lcd.print("T:");
	lcd.setCursor(9, 1);
	lcd.print("H:");
}

void loop(void) {
	g_realTemperature = getTemp(); //Получаем текущую температуру
	g_DHTTemperature = getDHTTemperature();
	g_DHTHumidity = getDHTHumidity();
	temperatureControl(); //Регулируем температуру
	printTempLCD(); //Печатаем текущую температуру
	printHumidityLCD();
	printHeaterStateLCD();
	wdt_reset(); //Сбрасываем wdt каждый цикл
}
