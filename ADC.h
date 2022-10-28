#ifndef _ADC_
#define _ADC_

#include "FIFO_Circular.h"

class ADC {
    public:
        ADC(int canal){
            // Zerando o ADMUX e garantindo que o canal
            // possa assumir valores de 0 até 15
            // canais->ADMUX = (canais->ADMUX & 0x0f) | (canal & 0x0f); 
            registradores->ADMUX = (1 << 6) | (canal & 0x0f);

            // Define os bits ADEN, ADSC, ADATE, ADIE, ADPS2, ADPS1 e ADPS0 para 1
            registradores->ADCSRA |= (1 << 7); // ADEN
            registradores->ADCSRA |= (1 << 5); // ADATE
            registradores->ADCSRA |= (1 << 3); // ADIE
            registradores->ADCSRA |= 0b00000111; // ADPS2, ADPS1 e ADPS0

            // Definindo os bits ADTS2, ADTS1 e ADTS0
            registradores->ADCSRB &= 0b11111000;

            // Habilitando interrupção global
            __asm__ ("sei");

            // Definindo o bit do ADSC para 1, iniciando
            // o ciclo de conversão
            registradores->ADCSRA |= (1 << 6); // ADSC 
        }

        int get(){
            // Retorna o último valor lido
            return ADC_FIFO.getLast();
        }

        int get_mean(){
            // Retorna a média de todos os valores lidos
            int resultado = 0;
            for (int c = 0; c < 16; c++){
                resultado += ADC_FIFO.get(c);
            }

            return resultado / 16;

        }

        static void ADC_Complete_handler(){
            ADC_FIFO.enqueue(registradores->ADC);
        }

    private:
        struct ADC_Registradores_t {
            // Mapeia 16 bis para o ADC.
            // int possui 16 bits, enquanto char possui 8 bits
            // int ADC já mapeia os registradores 0x78 (ADCL) e 0x79 (ADCH)
            unsigned int ADC;
            unsigned char ADCSRA;
            unsigned char ADCSRB;
            unsigned char ADMUX;  // Escolhe o pino e outras opções
        };

        static ADC_Registradores_t *registradores;
        static FIFO_C<int,16> ADC_FIFO;
};

#endif