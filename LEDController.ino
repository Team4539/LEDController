#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 10 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define B_PIN 7  // Arduino pin connected to the B wire.
#define NUM_LEDS 10 // Number of NeoPixels
#define pwmPin  3 // Change this to the pin you've connected the PWM signal to



String Mode = "game time"; // Set the initial mode to off.
int Pulse; 

CRGB leds[NUM_LEDS]; // Declare the 'leds' array before calling the 'FastLED.addLeds' function.

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, B_PIN, RGB>(leds, NUM_LEDS);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pwmPin, INPUT);

   // Startup sequence
  for(int i = 0; i < NUM_LEDS; i++) {
    CRGB color = (i / 4) % 2 == 0 ? CRGB(255, 102, 0) /*safety orange*/ : CRGB(37, 150, 190); /*Eastern blue*/
    leds[i] = color;
    FastLED.show();
    delay(100);
     
  }
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
  Mode = "game time";
} else if (Pulse > 5000 && Pulse <= 15000){
  Mode = "Idle";
}else {
  Mode = "Auto";
}


if (distance == 0){
  for (int i = 0; i < NUM_LEDS; i++) {
    // Red color
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(500); // Delay for half a second

    // Orange color
    leds[i] = CRGB(255, 102, 0);
    FastLED.show();
    delay(500); // Delay for half a second
  }
}
else if (Mode == "Idle") {
  for(int i=0; i < NUM_LEDS ; i++) {
       if(i % 4 <2) {
        leds[i] = CRGB(255, 102, 0); //safety orange (Kaotic main color)
    } else {
        leds[i] = CRGB(37, 150, 190); // Eastern blue color (Kaotic secondary color)
    };
  }
} else if (Mode == "Auto" && distance > 10) {
  for(int i=0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(246, 7, 250); // Purple color.
  }
} else if (Mode == "Auto" && distance < 10) {
  for(int i=0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(7, 246, 250); // Cyan color.
  }
} else if (Mode == "game time" && distance > 10) {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0); // Red color.
  }
} else {
  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 0)); // Turn off the LEDs.

  FastLED.show();
  delay(50);
}
}