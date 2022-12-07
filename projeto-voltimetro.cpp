#include "projeto.h"

volatile int botao_escala = 0;

enum State_t {
  WAIT = 0,
  ADQUIRE_ENTRADAS = 1,
  PROCESSA_V = 2,
  PROCESSA_mV = 3,
  IMPRIME_SAIDA = 4
};

State_t estado = WAIT;
TIMER0 timer;
ADC adc(0);
FilaDeFuncao ffuncao;
Alarme alarme(&ffuncao);
Evento volt;

UART Serial(9600);

void botao_isr(){
    static unsigned long ultima_interrupcao = 0;
    static unsigned long tempo_botao = 50;
    
    unsigned long agora = timer.micros();

    if (agora - ultima_interrupcao >= tempo_botao) {
      botao_escala = 1;
      ultima_interrupcao = agora;
    }
}

GPIO_Pin botao_hold(GPIO_Pin::GPIO_PORTD, GPIO_Pin::GPIO_PIN_2, GPIO_Pin::GPIO_INPUT);
GPIO_Pin botao_escala_fisico(GPIO_Pin::GPIO_PORTD, GPIO_Pin::GPIO_PIN_3, GPIO_Pin::GPIO_INT_RISING, botao_isr);

unsigned long medida;
unsigned long parte_decimal = 0;
unsigned long parte_inteira = 0;

State_t processo_atual = PROCESSA_V;

int a0 = 0;

void voltimetro(void * arg) {
  alarme.agenda(volt);

  // Atualizar entrada
  __asm__("cli");
  int b = botao_escala;
  botao_escala = 0;
  __asm__("sei");

  // Estados
  switch (estado){
    case WAIT:
      estado = ADQUIRE_ENTRADAS;
      // timer.delay(500000);
      break;

    case ADQUIRE_ENTRADAS:
      a0 = adc.get_mean();

      if (b == 1 ) {
        if (processo_atual == PROCESSA_V) estado = PROCESSA_mV;
        else if (processo_atual == PROCESSA_mV) estado = PROCESSA_V;
      } else estado = processo_atual;

      processo_atual = estado;
      break;

    case PROCESSA_V:
      if (botao_hold.get() == 1) estado = WAIT;
      else {
        estado = IMPRIME_SAIDA;
        medida = (((long) adc.get_mean()) * ((long) 5000000 / (long) 1023)) / 1000;
        parte_inteira = medida / 1000;
        parte_decimal = medida % 1000;
      }
      break;

    case PROCESSA_mV:  
      if (botao_hold.get() == 1) estado = WAIT;
      else {
        estado = IMPRIME_SAIDA;
        medida = (((long) a0) * ((long) 5000000 / (long) 1023)) / 1000;
      }
      break;

    case IMPRIME_SAIDA: 
      estado = WAIT;
      char saida[16];

      if (processo_atual == PROCESSA_V) {
        sprintf(saida, "%ld, %ld", parte_inteira, parte_decimal);
        Serial.println(saida);

      }
      else {
        sprintf(saida, "%d", medida);
        Serial.println(saida);
      }
      break;
  }
}

void setup() {
  Serial.println("setup");
  timer.registraObservador(&alarme);

  volt.tempo = 200000;
  volt.funcao = voltimetro;
  volt.args = (void *) 'a';
  alarme.agenda(volt);
}

void loop(){
  ffuncao.executar();
}