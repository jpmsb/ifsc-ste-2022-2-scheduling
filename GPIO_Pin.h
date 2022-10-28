#ifndef __GPIO_PIN__
#define __GPIO_PIN__

class GPIO_Pin {
    public:
        typedef void (*HandlerFunc)(void);
        static HandlerFunc handlers[2];

        enum GPIO_Port_t {
            GPIO_PORTB = 0x23,
            GPIO_PORTC = 0x26,
            GPIO_PORTD = 0x29
        };

        enum GPIO_Direction_t {
            GPIO_INPUT = 0,
            GPIO_OUTPUT = 1,
            GPIO_INT_LOW = 2,
            GPIO_INT_CHANGE = 3,
            GPIO_INT_FALLING = 4,
            GPIO_INT_RISING = 5
        };

        enum GPIO_PinNumber_t {
            GPIO_PIN_0 = 0,
            GPIO_PIN_1,
            GPIO_PIN_2,
            GPIO_PIN_3,
            GPIO_PIN_4,
            GPIO_PIN_5,
            GPIO_PIN_6,
            GPIO_PIN_7
        };

        GPIO_Pin(GPIO_Port_t _port, GPIO_PinNumber_t _pin, GPIO_Direction_t _dir, void (*_func)(void) = 0){
            port = (PortRegisters_t *) _port;
            pin_mask = 1 << _pin;

            if (_dir == GPIO_INPUT){
                // *DDR &= ~btn12_mask
                port->ddr &= ~pin_mask;
            } else if (_dir == GPIO_OUTPUT){
                // *DDRB |= led_mask;
                port->ddr |= pin_mask;

            } else { // Interrupção - INT0 e INT1
                int interrupt = _pin - 2;
                int edge = _dir - 2;
                unsigned char mask = (3 << interrupt * 2);

                *EICRA = (*EICRA & ~mask | (edge << interrupt * 2));

                // Exempo para o cálculo acima
                //      XXXX ??XX
                // & ~  0000 1100
                //   |_>1111 0011
                //      _________
                //      XXXX 00XX

                *EIMSK |= (1 << interrupt);
                handlers[interrupt] = _func;
            }
        }

        bool get() {
            return ((port->pin & pin_mask) > 0);
        }
        void set(bool value){
            if (value == 0) port->port &= ~pin_mask;
            else if (value > 0) port->port |= pin_mask;
        }

        private:
            struct PortRegisters_t {
                volatile unsigned char pin;
                volatile unsigned char ddr;
                volatile unsigned char port;
            };

            static volatile unsigned char * EICRA;
            static volatile unsigned char * EIMSK;

            PortRegisters_t *port;
            unsigned char pin_mask;
           
    };

#endif