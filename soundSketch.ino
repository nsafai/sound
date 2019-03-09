#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#define NUM_LEDS 256
#define DATA_PIN 6

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  delay(3000);
  Serial.begin(9600);
  matrix.begin();
}

void loop() {
//  printRainbowText("Hell yeah !");
//  getMicData();
  int micValue = getMicData() * 100 / 3 - 1;
  Serial.println(micValue);
  matrix.fillScreen(0);
  matrix.fillRect(0, 0, micValue/1.25, 3, matrix.Color(0, 130, 0)); 
  matrix.fillRect(0, 3, micValue, 2, matrix.Color(130, 0, 0)); 
  matrix.fillRect(0, 5, micValue/1.5, 3, matrix.Color(0, 0, 130)); 
  matrix.show();
}

//void drawVisualizer {
// 
//}

float getMicData() {
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
       if (sample > signalMax)
       {
          signalMax = sample;  // save just the max levels
       }
       else if (sample < signalMin)
       {
          signalMin = sample;  // save just the min levels
       }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

  return(volts);
}


