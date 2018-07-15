# M0PUH's morse bleeper

This is a little program which currently takes a supplied string of text 
and converts it to morse, which it then attempts to "send" using PORTB4.

In my current prototype, this (is simply connected to an LED, via a series 330 Ohm resistor, which then connects to ground.

The code also pulls PORTB0 high while it's sending data, so you can see when
it's done.

Finally, this code is designed to run on an ATiny45 Microcontroller, which
is currently more than powerful enough to handle the program. I used this
because I happened to have one. I expect that it will work with any Atmel
micro.

## Tunables

* You may wish to change the output port. To do this, change the macro
`OUTPUT_PORT` macro definition.
* You might want to change the time interval. This is set to 250ms by
  default, using the following [rules](http://www.rsgbshop.org/acatalog/Online_Catalogue_Morse_Code_12.html):
    * a dit (dot) is one unit long.
    * a dah (dash) is three units long.
    * The space between symbols in the same letter is one unit long.
    * The space between letters is three units long.
    * The space between words is seven units long.

## TODO

- [ ] Add more morse symbols
- [ ] Add random string generation mode with toggleable extras, like numbers, symbols etc.
- [ ] Design a simple oscillator circuit.
- [ ] Add support for keys so you can make noises.

## Warnings

Whoah, C. This is the first C I've written for a long time and the first
AVR-GCC C I've written for even longer. So it might be a bit crusty in
places, but it works for me!
