# attiny84 power-on reset generator

There are lots of power-on reset generator ICs available.  If you don't have one available, but you *do* have a microcontroller, you can just use that instead!

This is an example firmware for the [ATtiny84](http://www.mouser.com/ds/2/268/doc8006-1066127.pdf) microcontroller that generates a 500 ms reset pulse on PA0 when powered on.

If you connect a pushbutton to PA1 that connects to ground when pressed, a manual reset signal will be asserted on PA0 when the button is pressed.

No doubt you could adapt this firmware for other ATtiny variants.

Run the command

```
make
```

to compile the code, and

```
make program
```

to load the program onto the chip using `avrdude`.  You might need to edit the Makefile depending on which programmer you have.
