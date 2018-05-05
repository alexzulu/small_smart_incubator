float getTemp (){
 float celsius;
 sensors.requestTemperatures();
 celsius = sensors.getTempC(TL0);
 if(debug == 1){
  Serial.print("Temp C: ");
  Serial.println(celsius);
 }
 realTemp = celsius;
}

float old;
void printTempLCD(){
  float current = realTemp;
  if(old != current){
    lcd.setCursor(9, 1);
    lcd.print("     ");
    lcd.setCursor(9, 1);
    lcd.print(current);
    old = current;
  }
  lcd.setCursor(15, 0);
  lcd.print(heaterState);
}

void tempControl(){
  if(realTemp < setTemp){
    if(heaterState == 0 && digitalRead(HEATER_PIN) == LOW){
      digitalWrite(HEATER_PIN,HIGH);
      heaterState = !heaterState;
      Serial.println(digitalRead(HEATER_PIN));
    }
  }
  if(realTemp >= setTemp){
    if(heaterState == 1 && digitalRead(HEATER_PIN) == HIGH){
      digitalWrite(HEATER_PIN,LOW);
      heaterState = !heaterState;
      Serial.println(digitalRead(HEATER_PIN));
    }
  }
}

