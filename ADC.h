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

            // Define os bits ADEN, ADSC, ADPS2, ADPS1 e ADPS0 para 1
            registradores->ADCSRA |= (1 << 7) | (1 << 6) | (1 << 5) | (1 << 3) | (0 << 7);

            // Definindo os bits ADTS2, ADTS1 e ADTS0
            registradores->ADCSRB &= 0b11111000;

        }

        int get(){
            // Define os bits ADEN, ADSC, ADPS2, ADPS1 e ADPS0 para 1
            // registradores->ADCSRA = (registradores->ADCSRA | 0xc7);

            // Caso seja a primeira vez, o cálculo é feito novamente
            // if (primeiro) registradores->ADCSRA = (registradores->ADCSRA | 0xc7);
            // primeiro = false;

            // (Polling) Enquando o bit ADSC (6) for 1, espere
            // while(registradores->ADCSRA & (1 << 6));  // implementar por interrupção

            return ADC_FIFO.getLast();
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
        bool primeiro = true;
        static FIFO_C<char,16> ADC_FIFO;
};

#endif