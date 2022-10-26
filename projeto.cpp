#include "projeto.h"

UART uart(9600);
ADC adc(0);

void int0_isr();

GPIO_Pin led(GPIO_Pin::GPIO_PORTB, GPIO_Pin::GPIO_PIN_5, GPIO_Pin::GPIO_OUTPUT);
GPIO_Pin btn(GPIO_Pin::GPIO_PORTD, GPIO_Pin::GPIO_PIN_2, GPIO_Pin::GPIO_INT_RISING, int0_isr);

typedef FIFO <int, 10> MyFIFO;
MyFIFO fifo;

void int0_isr(){
    uart.put_string("INT0\n");
}

void setup(){
    uart.put_string("setup\n");
}

int x = -1;

void loop(){
    while (true){
        //led.set(1);
        //led.set(0);
        // uart.put(uart.get());
        // if (btn.get()){
            // uart.put_string("Lendo do ADC\n");
            // char str[16];
            // int dec = adc.get();
            // sprintf(str, "Lido: %d\n", dec);
            // // led.set(btn.get());
            // uart.put_string(str);
        // }
        // if (fifo.dequeue(&x) == MyFIFO::FIFO_SUCCESS){
        //     sprintf(str, "Desenfileirado: %d \n", x);
        //     uart.put_string(str);
        // }
        uart.put_string("Algo\n");
        busy_wait_delay(1);
        
    }
}