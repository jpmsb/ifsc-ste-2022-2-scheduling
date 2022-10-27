#include "ADC.h"

ADC::ADC_Registradores_t * ADC::registradores = (ADC_Registradores_t *) 0x78;
FIFO_C<int,16> ADC::ADC_FIFO;

extern "C" {
    void __vector_21() __attribute__ ((signal));
}

void __vector_21(){
    // chamar o tratador da interrupção de recebimento
    ADC::ADC_Complete_handler();
}