#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#define NUM_LEDS 256
#define DATA_PIN 6
#define NUM_COLORS 8

const int sampleWindow = 8; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0),
  matrix.Color(255, 63, 0),
  matrix.Color(255, 127, 0),
  matrix.Color(255, 255, 0),
  matrix.Color(0, 255, 0),
  matrix.Color(0, 0, 255),
  matrix.Color(75, 0, 130),
  matrix.Color(238, 130, 238)
};

void setup() {
  delay(3000);
  Serial.begin(9600);
  matrix.begin();
}

void loop() {
  drawVisual();
}

void drawVisual() {
  int micValue = getMicData() * 100 / 3 - 1;
  Serial.println(micValue);
  matrix.fillScreen(0);
  matrix.setBrightness(40); // for power consumption
  for (int i=0; i < NUM_COLORS; i++) {
    matrix.fillRect(0, i, getMicData() * 100 / 3 - 1, 1, colors[i]); 
  }
  matrix.show();
}

float getMicData() {
  unsigned long startMillis = millis();  // Start of sample window
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


