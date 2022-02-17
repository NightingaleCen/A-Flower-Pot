/*
 * utils.cpp
 * 提供花盆各项功能的库
 */
#include "Arduino.h"

#include "Wire.h"
#include "U8g2lib.h"
#include "Adafruit_SHT31.h"
#include "utils.h"

/*返回当前环境光照强度的百分比数值*/
int lightDetect(const int sensorPin)
{
    int val = analogRead(sensorPin);
    return (100 - map(val, 0, 1023, 0, 100));
}

/*返回当前土壤湿度百分比数值*/
int humidityDetect(const int sensorPin)
{
    int val = analogRead(sensorPin);
    return (100 - map(val, HUMIDITY_IN_WATER, HUMIDITY_IN_AIR, 0, 100));
}

/*载入安科拉长角牛*/
void loadTheCow(U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2)
{

    u8g2.firstPage();
    do
    {
        u8g2.drawXBMP(0, 0, 128, 64, cow);
    } while (u8g2.nextPage());
}
/*改变单次灌溉时长*/
void changeWaterDuration(int &waterDuration, int signal, U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2)
{
    switch (signal)
    {
    case INCREASE_SIGNAL:
        if (waterDuration < 10 * ONE_SEC)
            waterDuration += ONE_SEC;
        break;
    case DECREASE_SIGNAL:
        if (waterDuration > 1 * ONE_SEC)
            waterDuration -= ONE_SEC;
        break;
    default:
        return;
    }
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.firstPage();
    do
    {
        u8g2.drawStr(0, 16, "Current Water Duration is:");
        u8g2.setCursor(60, 32);
        u8g2.print(waterDuration / ONE_SEC, 1);
        u8g2.drawStr(42, 48, "Seconds");
    } while (u8g2.nextPage());
}

/*显示信息*/
void displayInf(U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2, Adafruit_SHT31 sht31)
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
        u8g2.print(humidityDetect(HUMIDITY_SENSOR_PIN), 1); //显示湿度
        u8g2.drawStr(0, 60, "Illumination :           %");
        u8g2.setCursor(85, 60);
        u8g2.print(lightDetect(LIGHT_SENSOR_PIN), 1); //显示环境光强
    } while (u8g2.nextPage());
}