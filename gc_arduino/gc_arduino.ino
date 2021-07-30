#include <Adafruit_DotStar.h>

#define NUMPIXELS 3 // Number of LEDs in strip

#define DATAPIN    13
#define CLOCKPIN   11
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_RGB);

unsigned long startTime;
unsigned long startCooldownTime;

int cooldownTime = 5000;

int currentSensorValue;
int pastSensorValue = 0;
int difference;

float pulseMod = -0.6;
int pulseTime = 2000;

int pulseState = 0;

float brightness = 255;

int pot1Pin = A2;
//int pot2Pin = A4;

int pot1Value = 0;
//int pot2Value = 0;

void setup() {
  Serial.begin(9600);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  startTime = millis();
  startCooldownTime = millis();
}

void loop() {
  currentSensorValue = analogRead(A0);
  difference = currentSensorValue - pastSensorValue;
  difference = abs(difference);

  if (difference > 300 && difference < 700) {
    startCooldownTime = millis();
    pulseState = 1;
  }
  if (difference > 700) {
    startCooldownTime = millis();
    pulseState = 2;
  }

  pot1Value = analogRead(pot1Pin);
  pot1Value = map(pot1Value, 0, 1023, 0, 255);

  for (int i = 0; i < 3; i++) {
    // Blue, Green, Red
    strip.setPixelColor(i, 55, 255, 0);
    strip.show();                     // Refresh strip
  }

  brightness += pulseMod;


  if (brightness > pot1Value) {
    brightness = pot1Value;
  }
  if (brightness < 0) {
    brightness = 0;
  }


  strip.setBrightness(brightness);
  strip.show();

  Serial.print(analogRead(A0));
  Serial.print("\n");

  if (millis() > startTime + pulseTime) {
    startTime = millis();
    pulseMod *= -1;
  }

  if (millis() > startCooldownTime + cooldownTime) {
    pulseState = 0;
  }


  switch (pulseState) {
    case 0:
      if (pulseMod > 0) {
        pulseMod = 0.6;
      }
      else {
        pulseMod = -0.6;
      }
      pulseTime = 2000;
      break;
    case 1:
      if (pulseMod > 0) {
        pulseMod = 2;
      }
      else {
        pulseMod = -2;
      }
      pulseTime = 1000;
      break;
    case 2:
      if (pulseMod > 0) {
        pulseMod = 4;
      }
      else {
        pulseMod = -4;
      }
      pulseTime = 500;
      break;
  }

  pastSensorValue = currentSensorValue;

  delay(5);
}
