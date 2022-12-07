#ifndef _UART_
#define _UART_

#include "FIFO.h"

class UART { 
    public:
        enum UART_Baudrate_t {
            UART_9600 = 103,
            UART_14400 = 68,
            UART_19200 = 51
        };

        UART(int baud = 9600, int data_bits = 8, int paridade = 0, int stop_bits = 1) {
            begin(baud, data_bits, paridade, stop_bits);
        }

        void begin(int baud = 9600, int data_bits = 8, int paridade = 0, int stop_bits = 1){
            int UBRRn = (8000000/(8 * (long)baud)) - 1;

            /* Set baud rate */
            registradores->UBRRH = (unsigned char)(UBRRn >> data_bits) & 0x0f;
            registradores->UBRRL = (unsigned char)(UBRRn & 0x00ff);

            /* Enable receiver and transmitter */
            registradores->UCSRB = (1 << 7) | (1 << 4) | (1 << 3);

            /* Set frame format: 8data, 2stop bit */
            registradores->UCSRC = (3 << 1);
        }

        void put(char c){
            int retorno_fila;
            do {
            __asm__ ("cli");
            retorno_fila = TxFIFO.enqueue(c);
            registradores->UCSRB |= (1 << 5);
            __asm__ ("sei");
            } while (retorno_fila == FIFO<char,16>::FIFO_ERROR_FULL);
        }

        void put_string(char * s){
            put_string((const char *) s);
        }

        void put_string(const char * s){
            while (*s != '\0') put(*s++);
            
        }

        void println(const char * s){
            put_string((const char *) s);
            put('\n');
        }

        void print(const char * s){
            put_string((const char *) s);
        }
    
        char get(){
            char dados;
            while(RxFIFO.dequeue(&dados) != FIFO<char,16>::FIFO_SUCCESS);
            return dados;
        }

        static void RxC_handler(){
            RxFIFO.enqueue(registradores->UDR);
        }

        static void TxC_handler(){
            char dado;
            if (TxFIFO.dequeue(&dado) != FIFO<char,16>::FIFO_ERROR_EMPTY) {
                registradores->UDR = dado;
            } else registradores->UCSRB &= ~(1 << 5);

        }

    private:
        struct UART_Registradores_t {
            unsigned char UCSRA;
            unsigned char UCSRB;
            unsigned char UCSRC;
            unsigned char RESERVADO;
            unsigned char UBRRL;
            unsigned char UBRRH;
            unsigned char UDR;
        };
        
        static UART_Registradores_t *registradores;
        static FIFO<char,16> RxFIFO;
        static FIFO<char,16> TxFIFO;
};

#endif