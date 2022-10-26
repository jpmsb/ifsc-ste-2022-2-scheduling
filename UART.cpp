#include "UART.h"
// #include "FIFO.h"
 
UART::UART_Registradores_t *UART::registradores = (UART_Registradores_t*) 0xc0;
FIFO<char,16> UART::RxFIFO;
FIFO<char,16> UART::TxFIFO;

extern "C" {
    void __vector_18() __attribute__ ((signal));
    void __vector_19() __attribute__ ((signal));
}

void __vector_18(){
    // chamar o tratador da interrupção de recebimento
    UART::RxC_handler();
}

void __vector_19(){
    // chamar o tratador da interrupção de envio
    UART::TxC_handler();
}