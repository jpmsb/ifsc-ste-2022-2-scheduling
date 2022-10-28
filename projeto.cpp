#include "projeto.h"

UART uart(9600);
ADC adc(0);

void setup(){
    uart.put_string("setup\n");
}

void loop(){
    uart.println("Lendo do ADC");
    char str[16];
    int dec = adc.get_mean();
    sprintf(str, "Lido: %d", dec);
    uart.println(str);
    busy_wait_delay(1);
}