#ifndef __RealTime_H__
#define __RealTime_H__

#include <Arduino.h>


float Promedio_ADC(const char Canal, char Muestras);

unsigned char Puerto(const char Puerto, char Pines, const char Estado);

#endif
