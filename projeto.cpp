#include "projeto.h"

UART uart(9600);
TIMER0 timer;

ListaEncadeada<int, true, false, int> list;
char strbuf[64];

void setup(){
    __asm__ ("sei");
    list.insere(0,5);
    list.insere(1,3);
    list.insere(2,4);
    list.insere(3,1);
    uart.put_string("setup\n");
    sprintf(strbuf, "Tamanho da lista: %d", list.tamanho());
    uart.println(strbuf);

}

void loop(){
    while (list.tamanho() > 0) {
        sprintf(strbuf, "Desenfileirado: %d", list.remove_inicio());
        uart.println(strbuf); // 3 1 2 0
        timer.delay(1000000);
    }

}