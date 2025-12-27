#include "SRO.h"

const byte SRO::_bits[8] = {
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000001
};


// Constructor
SRO::SRO(uint8_t data, uint8_t clock, uint8_t latch, uint8_t NSRChain) : // Uso uint8_t porque... ¿que arduino va a tener mas de 256 pines?¿y quien encadenaria tantos registros?

_NSRChain(NSRChain), //
_data(data),         //
_clock(clock),       // Inicializamos las variables privadas con un valor delos parametros a penas ejecutamos el constructor
_latch(latch) {      //

if (_NSRChain == 0) _NSRChain=1; //Esta linea comprueba que no intentes inicializar con 0 registros. Si lo intentas, automaticamente te pone 1.

 _ShadowR = new uint8_t[_NSRChain](); //Solicitamos memoria, en este caso, suficiente para alojar un array con longitud dictaminada pòr _NSRChain
                                      //Y nos aseguramos de que este todo en 0 al añadir esos parentesis al final

pinMode(_data,OUTPUT);  //
pinMode(_clock,OUTPUT); //Colocamos los pines que conectan el registro de desplazamiento como salidas.
pinMode(_latch,OUTPUT); //

Clean(); //Ponemos todos los registros a 0 para evitar valores aleatorios

}

// Destructor
SRO::~SRO() { //Si, puse un destructor, aunque en arduino usarlo es mas raro que comer mayonesa sola. Está ahi por si algun usuario, en algun raro momento, necesita matar la instancia y liberar pines y memoria

  Clean(); //Dejamos el hardware en un estado conocido (Todo 0)
  
  delete[] _ShadowR; //Liberamos la memoria del array antes de destruir la instancia. (Notese que en el constructor pido memoria, y en el destructor la libero.
                     //Tambien, tengan en cuenta que usar memoria de esta forma dinamica es peligroso, y deben evitarla si es posible, pero aqui era necesario

  pinMode(_data,INPUT);   //
  pinMode(_clock,INPUT);  // Liberamos los pines poniendolos en su configuracion por defecto: Como entradas.
  pinMode(_latch,INPUT);  //
}

// Métodos
void SRO::Clean() {

  digitalWrite(_latch, LOW);                          //

  for(uint8_t i=0; i<_NSRChain; i++) { 						    //
    shiftOut(_data, _clock, LSBFIRST, 0b00000000);    // Colocamos todas las salidas de los registros a 0. Y con el bucle for lo repetimos tantas veces como registros de desplazamiento tengamos presentes.
    _ShadowR[i]=0b00000000;                           // Ponemos el shadow rgister tambien a 0
  }	

  digitalWrite(_latch, HIGH);                          //

}

void SRO::WriteMem(bool LState, uint16_t pin) {

  if (pin >= (uint16_t)(_NSRChain * 8)) return; // Esta linea... comprueba que no metas un pin invalido. Si la borras, podes acabar en una posicion de memoria fuera de  _ShadowR... Y corrompes memoria

  uint8_t _regDeAcceso=(pin)/8;             //
  uint8_t _pinDelReg=pin-8*_regDeAcceso;    // Les dejo la tarea de entender el porque de estas dos lineas

  if(LState){

    _ShadowR[_regDeAcceso] = _ShadowR[_regDeAcceso] | _bits[_pinDelReg];	//Si el parametro de la funcion es 1, modificara el byte, con un 1 en el bit que corresponde al pin del registro de desplazamiento indicado.
  }
  else{

    _ShadowR[_regDeAcceso] = _ShadowR[_regDeAcceso] & ~_bits[_pinDelReg];	//Si el parametro de la funcion es 0, modificara el byte, con un 0 en el bit que corresponde al pin del registro de desplazamiento indicado.
  }

}

void SRO::UpdateSR() {

  digitalWrite(_latch, LOW);
  
  uint8_t count=_NSRChain-1;
  
  for(uint8_t i=0; i<_NSRChain; i++)
  { 
    shiftOut(_data, _clock, LSBFIRST, _ShadowR[count]);
    count--;
  }

  digitalWrite(_latch, HIGH);

}

void SRO::DigitalWrite(bool LState, uint16_t pin){

  WriteMem(LState, pin);
  UpdateSR();

}

void SRO::TogglePin(uint16_t pin){

  if (pin >= (uint16_t)(_NSRChain * 8)) return; //Otra vez esta linea. En el metodo WriteMem se explica porque existe

  uint8_t _regDeAcceso=(pin)/8;           //
  uint8_t _pinDelReg=pin-8*_regDeAcceso;  // Recuerden la tarea que les dejé

  _ShadowR[_regDeAcceso] = _ShadowR[_regDeAcceso] ^ _bits[_pinDelReg]; // Leo el byte del shadow register, y aplico la operaxion XOR entre ese byte y la mascara del bit que quiero invertir


}

void SRO::ToggleRegister(uint8_t reg){

  if (reg > _NSRChain-1) return;    // Seguridad, si intentas escribir en un registro que no existe, el metodo sale

  _ShadowR[reg]=~_ShadowR[reg];     //Busco la posicion perteneciente al registro de desplazamiento en el shadow register y la niego
  
}

void SRO::ToggleChain(){

  for(uint8_t i=0; i<_NSRChain; i++) {
     _ShadowR[i]=~_ShadowR[i];          //Recorro todas las posiciones del Shadow register, y niego los bytes
  }
}

void SRO::WriteGroup(uint8_t reg, uint8_t Value){

  if (reg > _NSRChain-1) return; // En el metodo ToggleRegister aparece esta linea, aca sirve para lo mismo

  _ShadowR[reg]=Value; //Escribo en la posicion que pertenece al registro elejido, en el shadow register  

}
