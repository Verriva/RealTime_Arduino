#include "RealTime.h"

bool Flag = 0;
bool Salida = 0;

float Steps = 0;

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

float Sensor_LM35(float Sensor)
{
  /*  Esta funcion realiza la conversion de la lectura del ADC a temperatura
      del sensor LM35.                                                    */

  Sensor = (5.0 * Sensor * 100.0)/1024;
  return Sensor;

}

void Puente_H_L298(const char IN1, const char IN2, const char SENTIDO, bool Enable, const char DutyCicle)
{
  if(SENTIDO == 'D' && Enable == HIGH)
  {
    //analogWrite(IN1, DutyCicle);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if(SENTIDO == 'I' && Enable == HIGH)
  {
    //analogWrite(IN2, DutyCicle);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

}

bool Control_ON_OFF(float SetPoint, float Medicion)
{
  /*  Esta funcion realiza el control ON-OFF, evaluando el valor de entrada
      con respecto al valor esperado, si el valor medido sobrepasa el valor
      esperado esta funcion regresara un valor VERDADERO :O                */
  bool Actuador = 0;

  if(Medicion < SetPoint)
  {
    return Actuador = 0;
  }
  else if (Medicion > SetPoint)
  {
    return Actuador = 1;
  }
}

bool Histeresis(float Entrada, float Limite, bool Estado)
{
  /*  Esta funcion regresa un valor booleano  Verdadero dependiendo si el
      valor de  Entrada es Verdadero en cuyo caso activara una bandera que
      mantendra el mismo valor booleano a la salida, hasta que la Entrada
      sea menor que el Limite.

      Esta funcion fue creada para complementarla con la funcion:
      Control_ON_OFF(float SetPoint, float Medicion), pero tambien puede ser
      utilizada en otra aplicacion.                   */

      if((Entrada >= Limite) && (Estado == 1))
      {
        Flag = 1;
        Salida = 1;
      }

      if(Flag == 1)
      {
        if(Entrada < Limite)
        {
          Flag = 0;
          return Salida = 0;
        }
        return Salida = 1;
      }
}

float Motor_Pasos(const char IN1, const char IN2, const char IN3, const char IN4, const char Direccion, int Delay)
{

  const char Puerto[4] = {IN1, IN2, IN3, IN4};

  int Paso[4][4] =
  {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
  };

  if(Direccion == 'D')
  {
    for(int i = 0; i < 4; i ++)
    {
      for(int j = 0; j < 4; j ++)
      {
        digitalWrite(Puerto[j], Paso[i][j]);
        //Serial.print(Paso[i][j]);
      }
      //Serial.println("    DERECHA");
      //delay(Delay);
      delayMicroseconds(Delay);
      Steps--;
    }
  }
  if(Direccion == 'I')
  {
    for(int i = 3; i >= 0; i --)
    {
      for(int j = 3; j >= 0; j --)
      {
        digitalWrite(Puerto[j], Paso[i][j]);
        //Serial.print(Paso[i][j]);
      }
      //Serial.println("    IZQUIERDA");
      //delay(Delay);
      delayMicroseconds(Delay);
      Steps++;
    }
  }

  return Steps;

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
      Lectura_Port |= Lectura_Pines;
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
        Lectura_Port |= Lectura_Pines;
    }
  }

  return Lectura_Port;
}
