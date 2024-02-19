#include <Arduino.h>
#line 1 "C:\\2024-code\\LEDController\\LEDController.ino"
#include <Adafruit_NeoPixel.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define LED_PIN      6  // Arduino pin connected to the NeoPixels.
#define NUM_LEDS     30 // Number of NeoPixels

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

String Mode = "off"; // Set the initial mode to off.

#line 12 "C:\\2024-code\\LEDController\\LEDController.ino"
void setup();
#line 21 "C:\\2024-code\\LEDController\\LEDController.ino"
void loop();
#line 12 "C:\\2024-code\\LEDController\\LEDController.ino"
void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Mode = "idle"; // Set the mode to idle.
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 74.676;
  Serial.print("Distance: ");
  Serial.println(distance); 
  Serial.print(" inches");

  if (distance < 10) {  
    Mode = "game time"; // Set the mode to game time.
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green color.
    }
  } else if (distance > 10 && Mode == "game time" ) {
    for (int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red color.
    }
  } else {
    for(int i=0; i<strip.numPixels(); i++) {
       if(i % 2 == 0) {
        strip.setPixelColor(i, strip.Color(255,102,0)); //safety orange (Kaotic main color)
    } else {
        strip.setPixelColor(i, strip.Color(37, 150, 190)); // Eastern blue color (Kaotic secondary color)
    };
  }
  strip.show();
  delay(50);
}
}
