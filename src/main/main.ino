#include <avr/wdt.h>//Подключаем библиотеку для работы с watch dog timer
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LCD_1602_RUS.h>

const float setTemperature = 37.80;//Установленная температура
const bool DEBUG = 0;//Вкл/откл режим отладки
const int controlDelay = 5000;//Задержка опроса.
const int ONE_WIRE_BUS = 9; //Нога на которой работает шина
const int TEMPERATURE_PRECISION = 12; //Разрешение датчика

LCD_1602_RUS lcd(0x27, 16, 2);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress TL0 = { 0x28, 0x6C, 0x91, 0xA9, 0x06, 0x00, 0x00, 0x31 };//Адрес датчика

#define SENSOR_PLUS 8//Питание датчика +
//#define SENSOR_MINUS 10//Питание датчика -
//#define LCD_PLUS 12//Питание экрана.
#define HEATER_PIN 7//Пин управления реле

float oldTemperature;//Предыдущее замерянное значение температуры
float realTemperature;//Реальная температура
bool heaterState = 0;//Состояние нагревателя
float lastTime = 0;//Время предыдущего замера
float lastRealTemperature = 38.00;//Предыдущее значение температуры

void setup() {
  //Инициализация пинов
//  pinMode(SENSOR_MINUS,OUTPUT);
//  digitalWrite(SENSOR_MINUS,LOW);
  pinMode(SENSOR_PLUS,OUTPUT);
  digitalWrite(SENSOR_PLUS,HIGH);
  
//  pinMode(LCD_PLUS,OUTPUT);
//  digitalWrite(LCD_PLUS,HIGH);
  
  pinMode(HEATER_PIN,OUTPUT);
  digitalWrite(HEATER_PIN,LOW);

  wdt_enable(WDTO_8S);//Включаем watch dog timer и ставим период 8 секунд

//  setTemperature = 37.80;//Устанавливаем температуру
//  controlDelay = 5000;
    
  Serial.begin(9600);
  if(DEBUG != 0){
    Serial.println("Debug mode ON");
  } else {
    Serial.println("Debug mode OFF");
  }
 
  sensors.begin();
  sensors.setResolution(TL0, TEMPERATURE_PRECISION);//Установка разрешения датчика

  lcd.init();//Инициализируем lcd
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print(L"Темпер.: ");
}

void loop(void) {
  realTemperature = getTemp();
  temperatureControl();
  printTempLCD();
  printHeaterStateLCD();
  wdt_reset();//Сбрасываем wdt каждый цикл
}
