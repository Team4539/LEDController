#include <Adafruit_NeoPixel.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define LED_PIN      6  // Arduino pin connected to the NeoPixels.
#define NUM_LEDS     30 // Number of NeoPixels
#define pwmPin  3 // Change this to the pin you've connected the PWM signal to


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

String Mode = "off"; // Set the initial mode to off.
int Pulse; 

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pwmPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  Pulse = pulseIn(pwmPin, HIGH);
  distance = (duration/2) / 74.676;
  
  Serial.print("Distance: ");
  Serial.println(distance); 
  Serial.print(" inches");

if (Pulse <= 5000){
  Mode = "Idle";
} else if (Pulse > 5000 && Pulse <= 15000){
  Mode = "Auto";
}else {
  Mode = "game time";
}



if (Mode == "Idle") {
  for(int i=0; i<strip.numPixels(); i++) {
       if(i % 2 == 0) {
        strip.setPixelColor(i, strip.Color(255,102,0)); //safety orange (Kaotic main color)
    } else {
        strip.setPixelColor(i, strip.Color(37, 150, 190)); // Eastern blue color (Kaotic secondary color)
    };
  }
} else if (Mode == "Auto" && distance > 10) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(246, 7, 250)); // Purple color.
  }
} else if (Mode == "Auto" && distance < 10) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(7, 246, 250)); // Cyan color.
  }
} else if (Mode == "game time" && distance > 10) {
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red color.
  }
} else {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green color.
  }

  strip.show();
  delay(50);
}
}