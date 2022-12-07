#ifndef __TIMER_H__
#define __TIMER_H__

#include "definicoes.h"
#include "lista_encadeada.h"
#include "observador.h"

class TIMER0 {
    public:
        static const unsigned char MAX = 255;
        static const unsigned char TOP = 199;
        static const unsigned char TIMER_BASE = MAX - TOP;
        static const unsigned int TIMER_RESOLUTION = 100;

        TIMER0(){
            registradores->TCCRB = 0x02;
            registradores->TCCRA = 0x00;
            registradores->TCNT = TIMER_BASE;

            // Ajustar o registrador TIMSK0 = 0x01 para ativar a interrupção do timer
            *TIMSK = 0x01;
            contador_useg = 0;
        }

        static Microssegundos micros(){
            return contador_useg;
        }

        static void timer0_isr_handler(){
            // contador_useg += 100;
            registradores->TCNT = TIMER_BASE;
            contador_useg += TIMER_RESOLUTION;
            
            Observador *obs = 0;
            for(int i = 0; i < observadores.tamanho(); i++){
                obs = observadores.obtem(i);
                obs->atualiza(TIMER_RESOLUTION);
            }
        }

        void registraObservador(Observador* obs){
            observadores.insere(obs);
        }

        void delay(Microssegundos d){
            Microssegundos end = micros() + d;
            while (end > micros());
        }

    private:
        struct Timer_Registradores_t {
            unsigned char TCCRA;
            unsigned char TCCRB;
            unsigned char TCNT;
        };

        static Timer_Registradores_t *registradores;
        static volatile unsigned char * TIMSK;    
        static Microssegundos contador_useg;

        static ListaEncadeada<Observador*, false, false> observadores;
};

#endif
