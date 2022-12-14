#include "projeto.h"

UART uart(9600);

FilaDeFuncao ffuncao;
TIMER0 timer;
Alarme alarme(&ffuncao);

Evento evt1, evt2;

void evt1_func(void * arg) {
    uart.println("Tarefa 0 - inicio");
    alarme.agenda(&evt1);
    timer.delay(2000000);
    uart.println("Tarefa 0 - fim");
}

void evt2_func(void * arg) {
    uart.println("Tarefa 1 - inicio");
    alarme.agenda(&evt2);
    timer.delay(2000000);
    uart.println("Tarefa 1 - fim");
}

void setup() {
    uart.println("setup");
    timer.registraObservador(&alarme);

    evt1.tempo = 4000000;
    evt1.funcao = evt1_func;
    evt1.args = (void*) 0;
    evt1.prioridade = 1;
    evt1.release_time = TIMER0::micros();

    evt2.tempo = 6000000;
    evt2.funcao = evt2_func;
    evt2.args = (void*) 0;
    evt2.prioridade = 2;
    evt2.release_time = TIMER0::micros();

    #if SCHED_TYPE == SCHED_FIFO
    alarme.agenda(&evt1);
    alarme.agenda(&evt2);
    #elif SCHED_TYPE == SCHED_RMS
    ffuncao.insere(&evt1, evt1.prioridade);
    ffuncao.insere(&evt2, evt2.prioridade);
    #elif SCHED_TYPE == SCHED_EDD
    ffuncao.insere(&evt1, evt1.tempo);
    ffuncao.insere(&evt2, evt2.tempo);
    #endif
}

void loop(){
    ffuncao.executar();
}