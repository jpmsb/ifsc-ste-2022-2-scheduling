#include "projeto.h"

UART uart(9600);

FilaDeFuncao ffuncao;
TIMER0 timer;
Alarme alarme(&ffuncao);

Evento t0, t1, t2, t3, t4;

void t0_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld EDD: T0 - inicio", TIMER0::micros()/1000000);

    uart.println(buff);
    // alarme.agenda(&t0);
    timer.delay(1000000); // e0 = 1 segundo

    sprintf(buff, "%ld EDD: T0 - fim", TIMER0::micros()/1000000);
    uart.println(buff);
}

void t1_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld EDD: T1 - inicio", TIMER0::micros()/1000000);

    uart.println(buff);
    // alarme.agenda(&t1);
    timer.delay(2000000); // e1 = 2 segundos

    sprintf(buff, "%ld EDD: T1 - fim", TIMER0::micros()/1000000);
    uart.println(buff);
}

void t2_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld EDD: T2 - inicio", TIMER0::micros()/1000000);

    uart.println(buff);
    // alarme.agenda(&t2);
    timer.delay(1000000); // e2 = 1 segundo

    sprintf(buff, "%ld EDD: T2 - fim", TIMER0::micros()/1000000);
    uart.println(buff);
}

void t3_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld EDD: T3 - inicio", TIMER0::micros()/1000000);

    uart.println(buff);
    // alarme.agenda(&t3);
    timer.delay(4000000); // e3 = 4 segundos

    sprintf(buff, "%ld EDD: T3 - fim", TIMER0::micros()/1000000);
    uart.println(buff);
}

void t4_func(void * arg) {
    char buff[32];
    sprintf(buff, "%ld EDD: T4 - inicio", TIMER0::micros()/1000000);

    uart.println(buff);
    // alarme.agenda(&t4);
    timer.delay(2000000); // e4 = 2 segundos

    sprintf(buff, "%ld EDD: T4 - fim", TIMER0::micros()/1000000);
    uart.println(buff);
}

void setup() {
    char buff[64];
    sprintf(buff, "%ld EDD - T3 perdeu seu prazo (exemplo 2)", TIMER0::micros()/1000);
    uart.println(buff);
    timer.registraObservador(&alarme);

    t0.tempo = 2000000; // d0: 2 segundos
    t0.funcao = t0_func;
    t0.args = (void*) 0;
    t0.prioridade = 1;
    t0.release_time = TIMER0::micros();

    t1.tempo = 5000000; // d1: 5 segundos
    t1.funcao = t1_func;
    t1.args = (void*) 0;
    t1.prioridade = 5;
    t1.release_time = TIMER0::micros();

    t2.tempo = 4000000; // d2: 4 segundos
    t2.funcao = t2_func;
    t2.args = (void*) 0;
    t2.prioridade = 3;
    t2.release_time = TIMER0::micros();

    t3.tempo = 8000000; // d3: 8 segundos
    t3.funcao = t3_func;
    t3.args = (void*) 0;
    t3.prioridade = 4;
    t3.release_time = TIMER0::micros();

    t4.tempo = 6000000; // d4: 6 segundos
    t4.funcao = t4_func;
    t4.args = (void*) 0;
    t4.prioridade = 2;
    t4.release_time = TIMER0::micros();

    #if SCHED_TYPE == SCHED_FIFO
    alarme.agenda(&evt1);
    alarme.agenda(&evt2);

    #elif SCHED_TYPE == SCHED_RMS
    ffuncao.insere(&evt1, evt1.prioridade);
    ffuncao.insere(&evt2, evt2.prioridade);

    #elif SCHED_TYPE == SCHED_EDD
    ffuncao.insere(&t0, t0.tempo);
    ffuncao.insere(&t1, t1.tempo);
    ffuncao.insere(&t2, t2.tempo);
    ffuncao.insere(&t3, t3.tempo);
    ffuncao.insere(&t4, t4.tempo);
    #endif
}

void loop(){
    ffuncao.executar();
}