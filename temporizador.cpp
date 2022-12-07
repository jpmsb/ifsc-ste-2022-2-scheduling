#include "temporizador.h"

TIMER0::Timer_Registradores_t * TIMER0::registradores = (Timer_Registradores_t*) 0x44;
volatile unsigned char * TIMER0::TIMSK = (volatile unsigned char *) 0x6e;
Microssegundos TIMER0::contador_useg;

ListaEncadeada<Observador*, false, false> TIMER0::observadores;

extern "C" {
    void __vector_16() __attribute__ ((signal));
}

void __vector_16(){
    // chamar o tratador do INT0
    TIMER0::timer0_isr_handler();
}