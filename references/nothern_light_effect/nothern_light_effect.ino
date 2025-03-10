// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  8

// NeoPixel brightness, 0 (min) to 255 (max)
//#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int fadeAmount = 5;    // how many points to fade the LED by
int LED_Brightness[LED_COUNT];

void setup() {
  int LED_Brightness[LED_COUNT] = {};
  for(int i=0; i<LED_COUNT; i++) {
    LED_Brightness[i]= 50+ (rand() % 155);
    }
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

  for(int i=0; i<LED_COUNT; i++) {
    LED_Brightness[i]= 100+ (rand() % 155);
    }
}

void loop() {
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(0,   255,   0)     , 50); // Red
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

void colorWipe(uint32_t color, int wait) {

  
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(LED_Brightness[i], 0, 0));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    
    LED_Brightness[i] = LED_Brightness[i] + fadeAmount;
    if (LED_Brightness[i] <= 50 || LED_Brightness[i] >= 255) {
    fadeAmount = -fadeAmount;
  }
    delay(10);                           //  Pause for a moment
  }
}
