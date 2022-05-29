#include <FAB_LED.h>

// On attiny85 the clock needs to be set to 16MHz (PLL) for FAB_LED to work.
// You can set it on the device with this command 
// (assuming you're using avrdude and usbasp as a programmer): 
// avrdude -p attiny85 -c usbasp  -U lfuse:w:0xE2:m -B5

const uint16_t numPixels = 1000; // Max: 64K pixels

ws2812b<D,1> myLeds;


static void colorWheel(uint8_t incStep, uint8_t & R, uint8_t & G, uint8_t & B)
__attribute__ ((always_inline));

static void colorWheel(uint8_t incStep, uint8_t & R, uint8_t & G, uint8_t & B)
{
  if (B == 0 && R != 0) {
    R = (R <= incStep) ? 0 : R - incStep;
    G = (G >= 255-incStep) ? 255 : G + incStep;
    return;
  }
  if (R == 0 && G != 0) {
    G = (G <= incStep) ? 0 : G - incStep;
    B = (B >= 255-incStep) ? 255 : B + incStep;
    return;
  }
  if (G == 0 && B != 0) {
    B = (B <= incStep) ? 0 : B - incStep;
    R = (R >= 255-incStep) ? 255 : R + incStep;
    return;
  }
}

void solid_color(uint8_t red, uint8_t green, uint8_t blue)
{
  rgb pix[1];

  pix[0].r = red;
  pix[0].g = green;
  pix[0].b = blue;

  // Disable interupts, save the old interupt state
  const uint8_t oldSREG = SREG;
  cli();

  // Display the LEDs
  for (uint16_t i = 0; i < numPixels; i++) {
    myLeds.sendPixels(1, pix);
  }

  // Restore the old interrupt state
  SREG = oldSREG;
}

void rainbow(uint8_t brightness)
{
  rgb pix[1];

  pix[0].r = brightness;
  pix[0].g = 0;
  pix[0].b = 0;

  for (uint16_t iter = 0; iter < 20 ; iter++) {
    const uint8_t oldSREG = SREG;
    cli();
    for (uint16_t i = 0; i < numPixels ; i++) {
      myLeds.sendPixels(1, pix);
      colorWheel(1, pix[0].r, pix[0].g, pix[0].b);
    }
    SREG = oldSREG;
    delay(100);
  }
}

void fade1N(uint8_t brightness, uint8_t incLevel)
{
  rgb pix[1];

  // Initialize the colors on the array
  pix[0].r = brightness;
  pix[0].g = 0;
  pix[0].b = 0;

  // Display the LEDs
  for (uint16_t iter = 0; iter < 20 ; iter++) {
    const uint8_t oldSREG = SREG;
    cli();
    for (uint16_t i = 0; i < numPixels ; i++) {
      myLeds.sendPixels(1, pix);
    }
    SREG = oldSREG;
    delay(100);

    // Rotate the colors based on the pixel's previous color.
    colorWheel(incLevel, pix[0].r, pix[0].g, pix[0].b);
  }
}


void setup()
{
  myLeds.clear(1000);
}

void loop()
{
//    delay(100);
//    solid_color(16, 0, 0);
//    delay(1000);
//    solid_color(0, 16, 0);
//    delay(1000);
//    solid_color(0, 0, 16);
//    delay(1000);
    rainbow(16);
    delay(100);
//    solid_color(16, 16, 16);
//    delay(1000);  
//    fade1N(16, 1);
//    delay(1000);
}
