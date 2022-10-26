#include "GPIO_Pin.h"

GPIO_Pin::HaldlerFunc GPIO_Pin::handlers[2];
volatile unsigned char * GPIO_Pin::EICRA = (volatile unsigned char *) 0x69;
volatile unsigned char * GPIO_Pin::EIMSK = (volatile unsigned char *) 0x3d;

extern "C" {
    void __vector_1() __attribute__ ((signal));
    void __vector_2() __attribute__ ((signal));
}

void __vector_1(){
    // chamar o tratador do INT0
    GPIO_Pin::handlers[0]();
}

void __vector_2(){
    // chamar o tratador do INT1
    GPIO_Pin::handlers[1]();
}