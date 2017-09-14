#include "RealTime.h"

float Promedio_ADC(const char Canal, char Muestras)
{
  /*  Esta funcion realiza un promedio de una lectura de cualquier puerto
      ADC, configurando el Canal se escoje el puerto ADC, configurando la
      variable muestras se escoge el numero de muestras que se escogeran
      para el promedio :)                                                  */

  int Mediciones[Muestras];
  float Promedio = 0;

  for(int i; i < Muestras; i++)
  {
    Mediciones[i] = analogRead(Canal);
    Promedio += Mediciones[i];
  }
  return Promedio /= Muestras;
}

unsigned char Puerto(const char Puerto, char Pines, const char Estado)
{
  /*  Esta funcion configura un puerto a utilizar en el Arduino UNO
      basandose en el tipo de puerto (PORTB, PORTC), la cantidad de
      pines a utilizar, y el estado que este requiera.                    */

  unsigned char Lectura_Pines;
  unsigned char Lectura_Port;
  char j = 0; //Por si las dudas

  if (Puerto == 'D')
  {
    //PORTD 0 - 7
    Pines += 2;
    for(int i = 2; i < Pines; i++)
    {
      j = i;
      pinMode(i, Estado);
      Lectura_Pines = digitalRead(i);
      Lectura_Pines = Lectura_Pines >> (j - 2);
      Lectura_Port += Lectura_Pines;
    }
  }
  else
  {
    //PORTB 8 - 13
    Pines += 8;
    for(int i = 8; i < Pines; i++)
    {
        j = i;
        pinMode(i, Estado);
        Lectura_Pines = digitalRead(i);
        Lectura_Pines = Lectura_Pines >> (j - 8);
        Lectura_Port += Lectura_Pines;
    }
  }

  return Lectura_Port;
}
