float getTemp (){
  float celsius;
  sensors.requestTemperatures();
  celsius = sensors.getTempC(TL0);
  if(DEBUG == 1){
    Serial.print("Temp C: ");
    Serial.println(celsius);
  }
  return celsius;
}

void printTempLCD(){
  float current = realTemperature;
  if(oldTemperature != current){
    lcd.setCursor(9, 1);
    lcd.print("     ");
    lcd.setCursor(9, 1);
    lcd.print(current);
    oldTemperature = current;
  }
}

void printHeaterStateLCD(){
  lcd.setCursor(15, 0);
  lcd.print(heaterState);
}

void tempControl(){
  if(realTemperature < setTemperature){
    if(heaterState == 0 && digitalRead(HEATER_PIN) == LOW){
      digitalWrite(HEATER_PIN,HIGH);
      heaterState = 1;
      if(DEBUG == 1){
        Serial.println(digitalRead(HEATER_PIN));
      }
    }
  }
  if(realTemperature >= setTemperature){
    if(heaterState == 1 && digitalRead(HEATER_PIN) == HIGH){
      digitalWrite(HEATER_PIN,LOW);
      heaterState = 0;
      if(DEBUG == 1){
        Serial.println(digitalRead(HEATER_PIN));
      }
    }
  }
}

