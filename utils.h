/*
 * utils.h
 * 提供花盆各项功能的库 
 */
#ifndef UTILS
#define UTILS

#include "Arduino.h"
#include "Wire.h"

const int TEN_SEC = 10000;

int lightDetect(const int sensorPin);

#endif