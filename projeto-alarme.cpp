#include "projeto.h"

UART uart(9600);

FilaDeFuncao ffuncao;
TIMER0 timer;
Alarme alarme(&ffuncao);

Evento evt1, evt2;

const char * MSG1 = "Oi, tudo bem?\n";
void printMsg1(void * arg)
{
    alarme.agenda(evt1);
    char * msg = (char *) arg;
    uart.put_string(msg);
}

const char * MSG2 = "ping\n";
void printMsg2(void * arg)
{
    alarme.agenda(evt2);
    char * msg = (char *) arg;
    uart.put_string(msg);
}

void setup()
{
    uart.println("setup");
    timer.registraObservador(&alarme);

    evt1.tempo = 1000000;
    evt1.funcao = printMsg1;
    evt1.args = (void*) MSG1;
    evt1.prioridade = 1;
    evt1.release_time = 0;
    alarme.agenda(evt1);

    evt2.tempo = 200000;
    evt2.funcao = printMsg2;
    evt2.args = (void*) MSG2;
    evt2.prioridade = 2;
    evt2.release_time = 0;
    alarme.agenda(evt2);
}

void loop(){
    ffuncao.executar();
}