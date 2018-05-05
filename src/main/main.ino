#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LCD_1602_RUS.h>

LCD_1602_RUS lcd(0x27, 16, 2);

#define ONE_WIRE_BUS 9 //Нога на которой работает шина
#define TEMPERATURE_PRECISION 12 //Разрешение датчика

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress TL0 = { 0x28, 0x6C, 0x91, 0xA9, 0x06, 0x00, 0x00, 0x31 };//Адрес датчика

#define SENSOR_PLUS 8//Питание датчика +
#define SENSOR_MINUS 10//Питание датчика -
#define LCD_PLUS 12//Питание экрана.
#define HEATER_PIN 7//Пин управления реле

float setTemp;//Установленная температура
float realTemp;//Реальная температура
bool heaterState = 0;//Состояние нагревателя
int debug = 0;//Вкл/откл режим отладки
int controlDelay;//Задержка опроса.
int lastMillis;

void setup() {
  pinMode(SENSOR_PLUS,OUTPUT);
  digitalWrite(SENSOR_PLUS,HIGH);
  pinMode(SENSOR_MINUS,OUTPUT);
  digitalWrite(SENSOR_MINUS,LOW);
  pinMode(LCD_PLUS,OUTPUT);
  digitalWrite(LCD_PLUS,HIGH);
  pinMode(HEATER_PIN,OUTPUT);
  digitalWrite(HEATER_PIN,LOW);

  setTemp = 37.80;
  controlDelay = 5000;
    
  Serial.begin(9600);
  if(debug != 0){
    Serial.println("Debug mode ON");
  } else {
    Serial.println("Debug mode OFF");
  }
 
  sensors.begin();
  sensors.setResolution(TL0, TEMPERATURE_PRECISION);

  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print(L"Темпер.: ");
}

void loop(void) {
  getTemp();
  tempControl();
  printTempLCD();
}
