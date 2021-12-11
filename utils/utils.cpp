/*
 * utils.cpp
 * 提供花盆各项功能的库 
 */
#include "Arduino.h"

#include "Wire.h"
#include "utils.h"

//返回当前环境光照强度的百分比数值
int lightDetect(const int sensorPin)
{
    int val = analogRead(sensorPin);
    return (100 - map(val, 0, 1023, 0, 100));
}

//返回当前土壤湿度百分比数值
int humidityDetect(const int sensorPin)
{
    int val = analogRead(sensorPin);
    return (100 - map(val,humidityInWater,humidityInAir,0,100));
}