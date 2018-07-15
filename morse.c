#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 1000000UL  /* 1 MHz Internal Oscillator */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LED1_PIN PB4 
#define LED2_PIN PB0 
#define UNIT_LENGTH 200
#define TOTAL_SYMBOLS 38 

void led_on()
{
    PORTB |= _BV(LED1_PIN);
}

void led_off()
{
    PORTB &= ~_BV(LED1_PIN);
}

void init()
{
    DDRB |= _BV(LED1_PIN);
}

typedef struct morseSymbol morseSymbol;

struct morseSymbol {
    char symbol;
    uint8_t length;
    uint8_t bits;
};

const struct morseSymbol letters[TOTAL_SYMBOLS] PROGMEM = {
    { 'A', 2, 0b10   },
    { 'B', 4, 0b0111 },
    { 'C', 4, 0b0101 }, 
    { 'D', 3, 0b011  },
    { 'E', 1, 0b1    },
    { 'F', 4, 0b1101 },
    { 'G', 3, 0b001  },
    { 'H', 4, 0b1111 },
    { 'I', 2, 0b11   },
    { 'J', 4, 0b1000 },
    { 'K', 3, 0b010  },
    { 'L', 4, 0b1011 },
    { 'M', 2, 0b00   },
    { 'N', 2, 0b01   },
    { 'O', 3, 0b000  },
    { 'P', 4, 0b1001 },
    { 'Q', 4, 0b0010 },
    { 'R', 3, 0b101  },
    { 'S', 3, 0b111  },
    { 'T', 1, 0b0    },
    { 'U', 3, 0b110  },
    { 'V', 4, 0b1110 },
    { 'W', 3, 0b100  },
    { 'X', 3, 0b0110 },
    { 'Y', 4, 0b0100 },
    { 'Z', 4, 0b0011 },

    { '1', 5, 0b10000 },
    { '2', 5, 0b11000 },
    { '3', 5, 0b11100 },
    { '4', 5, 0b11110 },
    { '5', 5, 0b11111 },
    { '6', 5, 0b01111 },
    { '7', 5, 0b00111 },
    { '7', 5, 0b00111 },
    { '8', 5, 0b00011 },
    { '9', 5, 0b00001 },
    { '0', 5, 0b00000 },

    { ' ', 3, 0b000  },
};
// Return the struct for a given symbol
const morseSymbol * struct_for_symbol(char symbol) {
    unsigned int length = TOTAL_SYMBOLS;
    const morseSymbol *table_symbol;
    for (unsigned int ii = 0; ii < length; ii++) {
        table_symbol = &(letters[ii]);
        if (pgm_read_byte(&(table_symbol->symbol)) == symbol ) {
            return table_symbol;
        }
    }

    return &(letters[10]);
}

void send_dit() {
    led_on();
    _delay_ms(UNIT_LENGTH);
    led_off();
}

void send_dah() {
    led_on();
    _delay_ms(UNIT_LENGTH);
    _delay_ms(UNIT_LENGTH);
    _delay_ms(UNIT_LENGTH);
    led_off();
}

void send_space(unsigned char spaces) {
    for (int ii = 0; ii < spaces; ii++) { 
        // Wants a compile time constant
        _delay_ms(UNIT_LENGTH);
    }
}

// Loop through the bits, and print dits and daaahs
// Text mode
uint8_t send_letter(uint8_t length, uint8_t bits) {

    unsigned int mask = 0x01 << (length - 1);

    for (unsigned int ii = 0; ii < length; ii++) {

        if ((bits & mask) == mask) {
            send_dit();
        }
        else {
            send_dah();
        }

        // The space between dits and dahs
        send_space(1);

        mask = mask >> 1;
    }

    // three unit spaces between letters
    send_space(2);

    return 0;
}

void send_message(const char message[], uint8_t len) {

    const morseSymbol *letter;

    for(int ii = 0; ii < len; ii++) {
        char str = pgm_read_byte(&(message[ii]));
        if (str == ' ') {
            // space between words is an extra 4 spaces.
            send_space(4);
        }
        else {
            letter = struct_for_symbol(str);
            send_letter(
                    pgm_read_byte(&(letter->length)),
                    pgm_read_byte(&(letter->bits))
                    );
        }
    }
}


int main() {
    init();

    static const char message[] PROGMEM = "MATT M0PUH";
    send_message(message, 10);
    return 0;
}
