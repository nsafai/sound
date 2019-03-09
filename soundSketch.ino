#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#define NUM_LEDS 256
#define DATA_PIN 6


 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  delay(3000);
  matrix.begin();
}


void printRainbowText(String text) {
  matrix.fillScreen(0);
  matrix.fillRect(0, 0, 8, 3, colors[0]); 
  matrix.fillRect(0, 3, 8, 2, colors[1]); 
  matrix.fillRect(0, 5, 8, 3, colors[2]); 
  matrix.show();
}

void loop() {
  printRainbowText("Hell yeah !");
//  rastaFlag();
  delay(50);
}

// where did we end: need to put loop inside of printRainbowText function
// use touch capacitor to change delay or word
// use switch to turn off


