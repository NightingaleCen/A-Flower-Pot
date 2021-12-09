#include <Arduino.h>
#include <U8g2lib.h>

#include "utils.h"
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup(void)
{
  sht31.begin(0x44);
  u8g2.begin();
}

void loop(void)
{
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.firstPage();
  do
  {
    u8g2.drawStr(0, 16, "Temperature   :           C");
    u8g2.setCursor(85, 16);
    u8g2.print(sht31.readTemperature(), 1); //显示温度
    u8g2.drawStr(0, 38, "Humidity       :           %");
    u8g2.setCursor(85, 38);
    u8g2.print(sht31.readHumidity(), 1); //显示湿度
    u8g2.drawStr(0, 60, "Illumination :           %");
    u8g2.setCursor(85, 60);
    u8g2.print(lightDetect(lightSensorPin), 1); //显示环境光强
  } while (u8g2.nextPage());
  delay(TEN_SEC);
}
