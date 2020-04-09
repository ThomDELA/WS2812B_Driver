
This is a small driver for WS2812b smart RGB leds with an example.
It will only work on some ATMEGA chips.
I tested only the ATMEGA328p.
It mostly uses AVR assembly to get the right timing, which is the critical part  of communicating with thoose leds.

Use atmel studio to open project. I use avrdude from adruino toolkit to upload into micro, simplest way is to copy arduino command line.

You should only reuse ledMatrix.* sources.
