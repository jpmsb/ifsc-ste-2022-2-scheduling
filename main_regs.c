// | - OU  bit a bit
// & - E   bit a bit
// ^ - XOR bit a bit

unsigned char * DDRB = (unsigned char *) 0x24;
const int led_pin = 5;
unsigned char led_mask;

unsigned char * PORTB = (unsigned char *) 0x25;

unsigned char * DDRD = (unsigned char *) 0x2A;
unsigned char * PIND = (unsigned char *) 0x29;
const int btn1_pin = 2;
const int btn2_pin = 3;
unsigned char btn1_mask;
unsigned char btn2_mask;
unsigned char btns_mask;

void setup(){
    // Config . DDRB

    // Ler
    // unsigned char tmp = *DDRB;

    // Modificar
    // tmp = tmp | led_mask;

    // Atualizar
    // *DDRB = tmp;

    // Versão dos três passos acima em
    // uma única linha
    // *DDRB = *DDRB | (1 << led_pin);
    // ou 
    // *DDRB = *DDRB | led_mask;
    led_mask = (1 << led_pin);
    btn1_mask = (1 << btn1_pin);
    btn2_mask = (1 << btn2_pin);
    btns_mask = btn1_mask | btn2_mask;
    *DDRB |= led_mask;
	*DDRD &= ~btn1_mask;

}

void ligaLED(){
    *PORTB |= led_mask;
}

void desligaLED(){
    *PORTB &= ~led_mask;
}

int leBotao(){
    // *PIND = 0000 0010 quando btn1 pressionado 
    // *PIND = 0000 0100 quando btn2 pressionado
    return btns_mask & *PIND; // 0000 0110 se 
                              // btns_mask e *PIND forem
                              // 0000 0110
}

void loop(){
    if (leBotao() == btns_mask){
        ligaLED();
    } else {
        desligaLED();
    }
}

int main(){
    setup();
    while(1) {loop();}
}