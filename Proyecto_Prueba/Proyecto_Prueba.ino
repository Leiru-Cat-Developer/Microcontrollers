#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Hola Mundo");
    lcd.setCursor(1,1);
    lcd.print("POR FIN");
}

void loop() {
}
