// SRO Significa Shift Register Output (Registro de desplazamiento de salida)
#ifndef SRO_h
#define SRO_h

#include <Arduino.h>

class SRO {
  public:
    // Constructor
    SRO(uint8_t data, uint8_t clock, uint8_t latch, uint8_t NSRChain); // Aqui se proporciona el pin de datos, reloj, latch y la cantidad de registros en cascada

    // Métodos públicos
    void Clean(); //Limpia todas las salidas del registro de desplazamiento y las pone en 0 (Tambien pone los shadow register a 0)
    void WriteMem(bool LState, uint16_t pin); // Escribe los estados en el shadow register
    void UpdateSR(); //Actualiza el estado de las salidas con los del shadow register
    void DigitalWrite(bool LState, uint16_t pin); //escribe en el shadow register y actualiza las salidas inmediatamente.

    void TogglePin(uint16_t pin);   //Invierte el estado logico de un pin SOLO en el shadow register
    void ToggleRegister(uint8_t reg); //Invierte el estado logico de un registro en especifico de la cadena SOLO en el shadow register
    void ToggleChain()  ;            //Invierte el estado logica de toda la cadena SOLO en el shadow register

    void WriteGroup(uint8_t reg, uint8_t Value); //Permite escribir un byte completo SOLO en el shadow register

     //Destructor de la clase 
    ~SRO();

  private:
    // Variables privadas
    uint8_t _data;   //
    uint8_t _clock;  // Variables interna de la clase 
    uint8_t _latch;  //
    uint8_t _NSRChain;// Cantidad de registros encadenados en cascada
    uint8_t* _ShadowR; //Puntero hacia el shadow register

    //Constantes privadas
    static const byte _bits[8];   // Aqui se almacenan las mascaras de bits

};

#endif
