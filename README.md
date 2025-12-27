# SRO – Shift Register Output para Arduino

Abstracción de pines de salida basada en registros de desplazamiento.

(Revise el archivo de licencia)

SRO (Shift Register Output) es una librería para Arduino que permite manejar
registros de desplazamiento de salida (como el CD4094 o 74HC595)
como si fueran pines digitales normales.

La librería mantiene un "shadow register" en memoria y sincroniza
las salidas físicas solo cuando el usuario lo indica explícitamente.

Esta librería no existe solo para "ahorrar pines".
Existe para permitir que un proyecto escale sin cambiar su arquitectura.

Con SRO podés:

- Manejar decenas o cientos de salidas usando pocos pines del microcontrolador
- Encadenar registros sin cambiar el código
- Modificar salidas individuales sin reescribir bytes a mano
- Separar el estado lógico del hardware real
- Actualizar las salidas solo cuando lo necesitás

SRO funciona con dos conceptos claros:

1. Shadow register:
   El estado lógico de todas las salidas vive en memoria. - El shadow register es la fuente de verdad.

2. UpdateSR():
   El hardware solo se actualiza cuando el usuario lo decide. - El hardware es solo un reflejo.

Ejemplo rapido:

#include <SRO.h>

SRO salidas(2, 3, 4, 2); // data, clock, latch, 2 registros (16 salidas) enumerados como 0 y 1

void setup() {
  salidas.DigitalWrite(HIGH, 0);  // Prende la salida 0
  salidas.DigitalWrite(HIGH, 7);  // Prende la salida 7
}

void loop() {
  salidas.TogglePin(0);  // Invierte la salida 0 (solo en memoria)
  salidas.UpdateSR();    // Sincroniza el hardware
  delay(500);
}

Nota: TogglePin() solo modifica el estado lógico en el shadow register.
El hardware se actualiza con UpdateSR().

SRO no:

- Lee entradas (para eso habrá una librería separada, a demas de que esta pensada para registros de desplazamiento SIPO)
- Actualiza el hardware de forma implícita (excepto el metodo DigitalWrite() y Clean())
- Usa SPI ni dependencias externas
- Oculta el funcionamiento de los registros

Esta librería está pensada para:

- Makers que usan registros de desplazamiento en proyectos medianos o grandes
- Personas que quieren orden y claridad en el manejo de salidas
- Estudiantes que quieren entender cómo abstraer hardware real

No está pensada para:

- Proyectos de 2 LEDs
- Código ultra-optimizado a nivel de ciclos
- Reemplazar GPIO directos cuando no hay necesidad

La documentación completa se encuentra en la Wiki del proyecto:

- Conceptos y modelo mental
- Explicación del shadow register
- Uso avanzado
- Ejemplos

SRO intenta mantener el "feel Arduino":
simple, explícito y sin magia.

Es C con clases, no un sistema operativo.

La documentación está en español como forma de aportar
material técnico claro fuera del anglocentrismo habitual.
(Tengo demasiadas malas anecdotas jaja.)
