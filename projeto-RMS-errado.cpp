#include "projeto.h"

UART uart(9600);

FilaDeFuncao ffuncao;
TIMER0 timer;
Alarme alarme(&ffuncao);

Evento t0, t1;

void t0_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld RMS: T0 - inicio", (TIMER0::micros()/1000) - 10);

    uart.println(buff);
    alarme.agenda(&t0);
    timer.delay(2001000);

    sprintf(buff, "%ld RMS: T0 - fim", (TIMER0::micros()/1000) - 10);
    uart.println(buff);
}

void t1_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld RMS: T1 - inicio", (TIMER0::micros()/1000) - 10);

    uart.println(buff);
    alarme.agenda(&t1);
    timer.delay(2000000);

    sprintf(buff, "%ld RMS: T1 - fim", (TIMER0::micros()/1000) - 10);
    uart.println(buff);
}

void setup() {
    char buff[64];
    sprintf(buff, "%ld RMS - t1 perdeu seu prazo (exemplo 2)", TIMER0::micros()/1000);
    uart.println(buff);
    timer.registraObservador(&alarme);

    // T0 = 4 segundos
    t0.tempo = 4000000;
    t0.funcao = t0_func; // e0 = 2 segundos
    t0.args = (void*) 0;
    t0.prioridade = 1;
    t0.release_time = TIMER0::micros();

    // T1 = 6 segundos
    t1.tempo = 6000000;
    t1.funcao = t1_func; // e1 = 2 segundos
    t1.args = (void*) 0;
    t1.prioridade = 2;
    t1.release_time = TIMER0::micros();

    #if SCHED_TYPE == SCHED_FIFO
    // alarme.agenda(&evt1);
    // alarme.agenda(&evt2);

    #elif SCHED_TYPE == SCHED_RMS
    ffuncao.insere(&t0, t0.prioridade);
    ffuncao.insere(&t1, t1.prioridade);

    #elif SCHED_TYPE == SCHED_EDD
    // ffuncao.insere(&evt1, evt1.tempo);
    // ffuncao.insere(&evt2, evt2.tempo);
    #endif
}

void loop(){
    ffuncao.executar();
}