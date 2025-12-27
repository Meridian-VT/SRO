/*
 Festa

 Enciende 8 leds a la vez en un patron aleatorio, para luego encenderlos en otro patron al azar, sigiendo esto infinitamente.
 Llame "Festa" al Sketch porque es la forma mal dicha(en la red social Discord) de la palabra fiesta, 
 ya que el encendido de los leds hace que parezcan luces de fiesta.   

 Escrito el 25 de Diciembre de 2025
 por Meridian-VT.
 
 Este Codigo de ejemplo es de dominio publico.
 
 */


#include <SRO.h> //incluimos la libreria en cuestion XD.

SRO FestaSR(2,3,4,1); // Creamos la instancia FestaSR. Parametros del Constructor: SRO FestaSR(PinDedatos, PinDeclock, PinDeEnable, NdeRegistrosEnCascada);  
long Nrandom=0;               //variable donde se guardara un numero aleatorio.

void setup()
{
/*Aqui no hace falta poner los pines 2,3,4 del arduino como salidas porque 
  la libreria lo hace de forma automatica al momento
  de crear la instancia.
*/
  randomSeed(analogRead(A0)); //establecemos como semilla de numeros aleatorios una entrada analogica desconectada (con ruido electrico).
}

void loop()
{

  Nrandom = random(0,2);         //Ponemos la variable Nrandom en un valor aleatorio entre 0 y 1.
  FestaSR.WriteMem(Nrandom,0); //Modificamos el estado del pin 0 en la memoria, poniendo un 0 o un 1 de forma aleatoria.
  Nrandom = random(0,2);         //Volvemos a poner la variable Nrandom en un valor aleatorio entre 0 y 1.
  FestaSR.WriteMem(Nrandom,1); //Modificamos tambien el estado del pin 1 en la memoria, poniendo un 0 o un 1 de forma aleatoria.
  Nrandom = random(0,2);         // Ya pillais que hace aqui.
  FestaSR.WriteMem(Nrandom,2); //(para los programadores avanzados) ¿Que si pude usar un bucle for...? Si podia pero me daba pereza, a demas es solo un programa de ejemplo.
  Nrandom = random(0,2);         // Ahora muchos llorareis. Waaa, waa como bebes. Todo porque hice un copy-paste del mismo par instrucciones 8 veces, en vez de usar un for.
  FestaSR.WriteMem(Nrandom,3); //
  Nrandom = random(0,2);         //
  FestaSR.WriteMem(Nrandom,4); //
  Nrandom = random(0,2);         //
  FestaSR.WriteMem(Nrandom,5); //
  Nrandom = random(0,2);         //
  FestaSR.WriteMem(Nrandom,6); //
  Nrandom = random(0,2);         //
  FestaSR.WriteMem(Nrandom,7); //
  FestaSR.UpdateSR(); //Una vez que se modificaron todos los valores de los pines en la memoria, se actualiza el registro una sola vez con esta función, enviando toda la cadena de bits completa. Esto con el fin de acelerar la operación, porque solo se actualiza una vez y la transferencia de datos es la parte mas lenta.
  delay(100); //Aqui esperamos un poquito antes de volver a empezar.
}
