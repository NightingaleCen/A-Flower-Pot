#include <IRremote.hpp>

#include "utils.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

unsigned long loopTime;
int waterDuration = 2 * ONE_SEC;//初始灌溉时长为2秒

void setup(void)
{
  sht31.begin(SHT31_ADDR);
  u8g2.begin();
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  loadTheCow(u8g2);//载入安科拉长角牛！
  loopTime = millis();
}

void loop(void)
{
  /*接收红外信号调整灌溉时长*/
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    if (millis() - loopTime > 5.2 * ONE_SEC) {
      changeWaterDuration(waterDuration, IrReceiver.decodedIRData.command, u8g2);
      loopTime = millis() - 5 * ONE_SEC;  
    }
  }
  /*显示信息*/
  else if (millis() - loopTime > 10 * ONE_SEC) {  //每十秒显示一次
    displayInf(u8g2, sht31);
    loopTime = millis();
  }
}
