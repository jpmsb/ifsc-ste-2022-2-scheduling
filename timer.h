#ifndef __TIMER_H__
#define __TIMER_H__

class Timer0 {
    public:
        typedef unsigned long long Microssegundos; // 64 bits

        Timer0(){
            registradores = (Timer_Registradores_t*) 0x44;
            registradores->TCCRB = 0x02;
            registradores->TCCRA = 0x00;
            // Ajustar o registrador TIMSK0 = 0x01 para ativar a interrupção do timer
            contador_useg = 0;
        }

        Microssegundos micros(){
            return contador_useg;
        }

        static void timer0_isr_handler(){
            contador_useg += 100;
        }

        void delay(Microssegundos d){
            Microssegundos end = micros() + d;
            while (micros() < end);
        }

    private:
        static Microssegundos contador_useg;
        struct Timer_Registradores_t {
            unsigned char TCCRA;
            unsigned char TCCRB;
            unsigned char TCNT;
        };

        Timer_Registradores_t *registradores;
        
};

#endif
