#include <Arduino.h>
#include <U8g2lib.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int timer = 0;
char timerstr[8];
int count = 1;
const char *nere = "Borsta nere";
const char *uppe = "Borsta uppe";
const char *msg = nere;
unsigned long DELAY_TIME = 1000; // 1.5 sec
unsigned long delayStart = 0;    // the time the delay started
bool delayRunning = false;       // true if still waiting for delay to finish

void setup(void)
{
  Serial.begin(9600);
  u8g2.begin();
  delayStart = millis();
  delayRunning = true;
}

void loop(void)
{
  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME))
  {
    delayStart += DELAY_TIME; // this prevents drift in the delays
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_8x13_tf);

    if (timer == 60 && count == 1)
    {
      count++;
      timer = 0;
      msg = uppe;
    }

    if (timer == 60 && count == 2)
    {
      u8g2.clearDisplay();
      u8g2.setFont(u8g2_font_10x20_tf);
      u8g2.drawStr(1, 32, "Klar!");
      u8g2.sendBuffer();
      while (1)
      {
      };
    }

    u8g2.drawStr(1, 10, msg);
    u8g2.drawHLine(1, 24, 120);
    u8g2.drawHLine(1,44, 120);
    u8g2.drawVLine(1, 24, 20);
    u8g2.drawVLine(121, 24, 20);
    u8g2.drawBox(1, 24, (timer * 2), 20);
    u8g2.sendBuffer();
    timer++;
  }
}