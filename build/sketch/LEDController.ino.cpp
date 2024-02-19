#include <Arduino.h>
#line 1 "C:\\2024-code\\LEDController\\LEDController.ino"
#include <Adafruit_NeoPixel.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define LED_PIN      6  // Arduino pin connected to the NeoPixels.
#define NUM_LEDS     30 // Number of NeoPixels

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#line 10 "C:\\2024-code\\LEDController\\LEDController.ino"
void setup();
#line 18 "C:\\2024-code\\LEDController\\LEDController.ino"
void loop();
#line 10 "C:\\2024-code\\LEDController\\LEDController.ino"
void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 74.676
   Serial.print("Distance: ");
  Serial.println(distance); 
  Serial.print(" inches");
  
  if (distance < 10) {  // Change this value to adjust the distance at which the sensor triggers the LEDs to turn green.
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green color.
    }
  } else {
    for(int i=0; i<strip.numPixels(); i++) {
      // Cycle through colors for idle phase.
      int r = (i * 256 / strip.numPixels()) % 256;
      int g = (i * 512 / strip.numPixels()) % 256;
      int b = (i * 1024 / strip.numPixels()) % 256;
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
  }
  strip.show();
  delay(50);
}
