//PUSH버튼

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define thou 2
#define fhun 3
#define hun 4
bool thou_flag = false;
bool fhun_flag = false;
bool hun_flag = false;
int sum = 0;

void setup()
{
  lcd.init();
  pinMode(thou, INPUT);
  pinMode(fhun, INPUT);
  pinMode(hun, INPUT);
}

void loop()
{
    if (digitalRead(hun) == 0)hun_flag = true;
    if (digitalRead(hun) == 1 && hun_flag == true)
    {
      hun_flag = false;
      sum += 100;
    }
    if (digitalRead(fhun) == 0)fhun_flag = true;
    if (digitalRead(fhun) == 1 && fhun_flag == true)
    {
      fhun_flag = false;
      sum += 500;
    }
    if (digitalRead(thou) == 0)thou_flag = true;
    if (digitalRead(thou) == 1 && thou_flag == true)
    {
      thou_flag = false;
      sum += 1000;
    }
  lcd.setCursor(0, 0);
  lcd.print(sum);
  delay(500);
}
