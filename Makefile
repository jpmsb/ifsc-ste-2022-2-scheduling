COMPONENTS := ADC.o GPIO_Pin.o UART.o projeto.o
APP := main.cpp

CC_FLAGS := -mmcu=atmega328p
# CC_FLAGS := -mmcu=atmega328p -Wl,-u,vfprintf -lprintf_flt  # habilita uso de floats no printf

all: $(COMPONENTS)
	avr-g++ $(CC_FLAGS) $(APP) $(COMPONENTS) -o main.elf
	avr-size main.elf
	avr-objcopy -O ihex main.elf main.ihex
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -U flash:w:main.ihex

%.o: %.cpp
	avr-g++ -mmcu=atmega328p -c $< -o $@

clean:
	rm -f *.o *.elf *.ihex