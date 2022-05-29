Arduino IDE project for the ws2812_tester.

This uses the [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) for
arduino IDE and is heavily based on an example from the
[FAB_LED](https://github.com/sonyhome/FAB_LED) library, which we use here.

To run this on an ATTiny85, you need to set it's clock to 16MHz. You can do
that by using the interal PLL by setting one of the fuses. If you're using
avrdude and an usbasp programmer, you can do that by running:

```
avrdude -p attiny85 -c usbasp  -U lfuse:w:0xE2:m -B5
```

This code is free software, distributed under the terms of the GNU General
Public License as published by the Free Software Foundation, version 2 of the
License. See the [LICENSE](./LICENSE) file for more information.
