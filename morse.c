#include <stdio.h>
#include <string.h>

typedef struct morseSymbol morseSymbol;

struct morseSymbol {
    char symbol;
    unsigned int length;
    unsigned int bits;
};

struct morseSymbol letters[] = {
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
morseSymbol struct_for_symbol(char symbol) {
    unsigned int length = sizeof(letters)/sizeof(letters[0]);
    for (unsigned int ii = 0; ii < length; ii++) {
       if ( letters[ii].symbol == symbol ) {
           return letters[ii];
       }
   }

   return letters[length-1];
}

void send_dit() {
    printf(".");
}

void send_dah() {
    printf("_");
}

void send_space(int spaces) {
    for (int ii = 0; ii < spaces; ii++) { 
        printf("/");
    }
}

// Loop through the bits, and print dits and daaahs
// Text mode
int send_letter(morseSymbol symbol) {

    fprintf(
            stderr,
            "symbol: %c %d, %d\n",
            symbol.symbol, symbol.bits, symbol.length
           );

    unsigned int mask = 0x01 << (symbol.length - 1);

    for (unsigned int ii = 0; ii < symbol.length; ii++) {

        fprintf(stderr, "%d: mask: %d\n", ii, mask);

        if ((symbol.bits & mask) == mask) {
            send_dit();
        }
        else {
            send_dah();
        }

        send_space(1);

        mask = mask >> 1;
    }

    // three unit spaces here. maybe followed by another 4
    send_space(2);

    return 0;
}

int main() {

    char message[] = "MATT M0PUH";
    int len = strlen(message);

    for(int ii = 0; ii < len; ii++) {
        if (message[ii] == ' ') {
            // space between words is an extra 4 spaces.
            send_space(4);
        }
        else {
            morseSymbol letter = struct_for_symbol(message[ii]);
            send_letter(letter);
        }
    }

    return 0;
}
