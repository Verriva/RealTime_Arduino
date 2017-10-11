#ifndef __RealTime_H__
#define __RealTime_H__

#include <Arduino.h>


float Promedio_ADC(const char Canal, char Muestras);

float Sensor_LM35(float Sensor);

void Puente_H_L298(const char IN1, const char IN2, const char SENTIDO, bool Enable, const char DutyCicle);

bool Control_ON_OFF(float SetPoint, float Medicion);

bool Histeresis(float Entrada, float Limite, bool Estado);

float Motor_Pasos(const char IN1, const char IN2, const char IN3, const char IN4, const char Direccion, int Delay);

unsigned char Puerto(const char Puerto, char Pines, const char Estado);

#endif
