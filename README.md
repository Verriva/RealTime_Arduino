# RealTime.h

Conjunto de Funciones para hacerte la vida mas facil!

## Descripcion

La libreria consta de varias funciones que te ayudaran a
simplificar tu codigo de programacion consta de las siguientes
funciones:

## float Promedio_ADC(const char Canal, char Muestras)

    Esta funcion realiza un promedio de una lectura de cualquier puerto
    ADC, configurando el Canal se escoje el puerto ADC, configurando la
    variable muestras se escoge el numero de muestras que se escogeran
    para el promedio :)

    Ejemplo:

    float Sensor = Promedio_ADC(A0,1);                                                 

## unsigned char Puerto(const char Puerto, char Pines, const char Estado)

    Esta funcion configura un puerto a utilizar en el Arduino UNO
    basandose en el tipo de puerto (PORTB, PORTC), la cantidad de
    pines a utilizar, y el estado que este requiera.

    Ejemplo:

    unsigned char Opcion = Puerto('D', 2, HIGH);


Diseñado por: [Josue Echeverria](https://www.facebook.com/josue.echeverria.583)

SuperTeam.
