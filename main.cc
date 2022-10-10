// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include "gpio_pin.h"
#include "uart.h"

void int0_isr();
void int1_isr();

GPIO_Pin btn0(GPIO_Pin::GPIO_PORTD,
             GPIO_Pin::GPIO_PIN_2,
             GPIO_Pin::GPIO_INT_RISING,
             int0_isr);
GPIO_Pin btn1(GPIO_Pin::GPIO_PORTD,
             GPIO_Pin::GPIO_PIN_3,
             GPIO_Pin::GPIO_INT_RISING,
             int1_isr);

UART uart(UART::UART_9600);

void int0_isr()
{
    uart.puts("INT0\n");
}
void int1_isr()
{
    uart.puts("INT1\n");
}

void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
}

void busy_wait_delay(int times)
{
    while (times--)
    {
        unsigned long x = 0x7ffff;
        while(x--) __asm__ ("nop");
    }
}

void loop()
{
    uart.puts("loop\n");
    busy_wait_delay(2);
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
