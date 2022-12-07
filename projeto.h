#ifndef __PROJETO_H__
#define __PROJETO_H__

#include "definicoes.h"
#include "UART.h"
#include "ADC.h"
#include "GPIO_Pin.h"
#include <stdio.h>
#include "temporizador.h"
#include "fila_de_funcao.h"
#include "lista_encadeada.h"
#include "alarme.h"

static void busy_wait_delay(int times){
    while (times--){
        unsigned long x = 0x7ffff;
        while(x--) __asm__ ("nop");
    }
}

void setup();
void loop();

#endif