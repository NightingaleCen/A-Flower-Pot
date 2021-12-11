/*
 * utils.h
 * 提供花盆各项功能的库 
 */
#ifndef UTILS
#define UTILS

#include "Arduino.h"
#include "Wire.h"

const int TEN_SEC = 10000;
const int SHT31_ADDR = 0x44;

const int lightSensorPin = 0;
const int humiditySensorPin = 1;
const int humidityInAir = 500;
const int humidityInWater = 180;

//返回当前环境光照强度的百分比数值
int lightDetect(const int sensorPin);

//返回当前土壤湿度百分比数值
int humidityDetect(const int sensorPin);

#endif