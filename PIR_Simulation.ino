//Hack for covid
//Codezoned

#include <LiquidCrystal.h>

LiquidCrystal lcd (13,12,11,10,9,8);
void setup() {
  lcd.begin (16,2);
  }
void loop()
{
  int pirstate=digitalRead(1);
  lcd.setCursor(0,0);
  lcd.print("goKorona");
  if(pirstate == LOW){
    lcd.setCursor(0,1);
    lcd.print("UV lights ON");
    delay(500);
    lcd.clear();
   }
   else if (pirstate == HIGH)
  {
    lcd.setCursor(0,1);
    lcd.print("UV lights OFF");
    delay(500);
    lcd.clear();
    }
 }
