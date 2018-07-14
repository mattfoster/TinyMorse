# AVR-GCC Makefile
PROJECT=morse
SOURCES=morse.c
CC=avr-gcc
OBJCOPY=avr-objcopy
MMCU=attiny45
PORT=/dev/tty.usbserial-A600eyob

CFLAGS=-mmcu=$(MMCU) -Wall -Os

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES) 
	$(CC) $(CFLAGS) -o $(PROJECT).out $(SOURCES)

program: $(PROJECT).hex
	avrdude -p t45 -c buspirate -P $(PORT) -e -U flash:w:$(PROJECT).hex
clean:
	rm -f $(PROJECT).o
	rm -f $(PROJECT).out
	rm -f $(PROJECT).map
	rm -f $(PROJECT).hex
