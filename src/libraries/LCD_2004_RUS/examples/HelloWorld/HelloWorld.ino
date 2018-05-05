#include <LCD_2004_RUS.h>

LCD_2004_RUS lcd(0x3F, 20, 4);

void setup()
{
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(L"ТЕМПЕРАТУРА");
  lcd.setCursor(0, 1);
  lcd.print(L"ВЛАЖНОСТЬ");
  lcd.setCursor(0, 2);
  lcd.print(L"ВЕНТИЛЯЦИЯ");
  lcd.setCursor(0, 3);
  lcd.print(L"ОСВЕЩЕННОСТЬ");

}

void loop()
{
}
