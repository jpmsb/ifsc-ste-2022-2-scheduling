// Arquivo: gpio_pin.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include "gpio_pin.h"

GPIO_Pin::HandlerFunc GPIO_Pin::handlers[2];
volatile unsigned char * GPIO_Pin::eicra = (volatile unsigned char *) 0x69;
volatile unsigned char * GPIO_Pin::eimsk = (volatile unsigned char *) 0x3d;

extern "C"
{
    void __vector_1() __attribute__ ((signal));
    void __vector_2() __attribute__ ((signal));
}

void __vector_1()
{
    // chamar o handler do INT0
    GPIO_Pin::handlers[0]();
}
void __vector_2()
{
    // chamar o handler do INT1
    GPIO_Pin::handlers[1]();
}
