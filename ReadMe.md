Small driver for WS2812b smart RGB leds.
It will only work on some ATMEGA chips, at least with ATMEGA328p.
It mostly uses AVR assembly to get the right timing, which is the critical part  of communicating with thoose leds.

Use atmel studio to open project. I use avrdude from adruino toolkit to upload into micro, simplest way is to copy arduino command line.
