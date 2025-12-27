/*
 Blink

 Enciende un led por un segundno, para luego apagarlo en el siguiente segundo, sigiendo esto infinitamente.
 Esta es una especie de refrito del blink original pero adaptado para trabajar con los pines del registro de desplazamiento.

 Escrito el 25 de Dicimbre de 2025
 por Meridian-VT.
 
 Este Codigo de ejemplo es de dominio publico.
 
 */


#include <SRO.h> //incluimos la libreria en cuestion XD.

SRO MySR(2,3,4,1); // Creamos la instancia MySR. Parametros del Constructor: PinExtra MySR(PinDedatos, PinDeclock, PinDeEnable, NdeRegistrosEnCascada);  
int pin=0;               //Pin De salida 0 del registro de desplazamiento.

void setup()
{
/*Aqui no hace falta poner los pines 2,3,4 del arduino como salidas porque 
  la libreria lo hace de forma automatica al momento
  de crear la instancia.
*/
}

void loop()
{
  MySR.DigitalWrite(pin , HIGH); // el pin 0 del registro se pone en 1 logico.
  delay(1000);                //Esperamos un segundo.
  MySR.DigitalWrite(pin, LOW); // el pin 0 del registro se pone en 0 logico.
  delay(1000);              //Volvemos a esperar 1 segundo.
}
