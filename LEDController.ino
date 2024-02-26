#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 10 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define B_PIN 7  // Arduino pin connected to the B wire.
#define NUM_LEDS 60 // Number of NeoPixels
#define pwmPin  3 // Change this to the pin you've connected the PWM signal to
#define pwmpinGround 13



String Mode = "game time"; // Set the initial mode to off.
int Pulse; 

CRGB leds[NUM_LEDS]; // Declare the 'leds' array before calling the 'FastLED.addLeds' function.

void setup() {
  
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, B_PIN, RGB>(leds, NUM_LEDS);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pwmPin, INPUT);
  pinMode(pwmpinGround, OUTPUT);
  digitalWrite(pwmpinGround, LOW);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  // Startup sequence
  for(int i = 0; i < NUM_LEDS; i++) {
    // Create a color based on the current LED's position
    // This will create a gradient effect across the LEDs
    uint8_t hue = map(i, 0, NUM_LEDS, 0, 255);
    
    // Set the LED to the calculated color
    leds[i] = CHSV(hue, 255, 255); // CHSV is a color model used in FastLED
    
    FastLED.show();
    delay(100); // Change this to control the speed of the flow
  }
  // Transition sequence to startup 2
for(int j = 0; j < 256; j++) {
  for(int i = 0; i < NUM_LEDS; i++) {
    CRGB color = ((i + j) / 4) % 2 == 0 ? CRGB(255, 102, 0) /*safety orange*/ : CRGB(37, 150, 190); /*Eastern blue*/
    // Blend the current color of the LED with the new color
    leds[i] = nblend(leds[i], color, j);
  }
  FastLED.show();
  delay(10); // Change this to control the speed of the transition
}
  // Startup 2 sequence
  int iterations = 600; // Number of iterations for 30 seconds
for(int k = 0; k < iterations; k++) {
  for(int i = 0; i < NUM_LEDS; i++) {
    CRGB color = ((i + k) / 4) % 2 == 0 ? CRGB(255, 102, 0) /*safety orange*/ : CRGB(37, 150, 190); /*Eastern blue*/
    leds[i] = color;
  }
  FastLED.show();
  delay(50);
}

// Smooth blinking
for(int j = 0; j < 10; j++) {
  // Fade out
  for(int k = 255; k >= 0; k -= 5) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(k);
    }
    FastLED.show();
    delay(10); // Change this to control the speed of the fade
  }

  // Fade in
  for(int k = 0; k <= 255; k += 5) {
    for(int i = 0; i < NUM_LEDS; i++) {
      CRGB color = (i / 4) % 2 == 0 ? CRGB(255, 102, 0) /*safety orange*/ : CRGB(37, 150, 190); /*Eastern blue*/
      leds[i] = color;
      leds[i].fadeToBlackBy(255 - k);
    }
    FastLED.show();
    delay(10); // Change this to control the speed of the fade
  }
}
}

void loop() {
  static unsigned long lastTriggerTime = 0;
  static unsigned long lastLEDUpdateTime = 0;
  long duration, distance;
  
  if (millis() - lastTriggerTime >= 1) {
    digitalWrite(TRIGGER_PIN, LOW);  
    delayMicroseconds(1); 
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(1); 
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    Pulse = pulseIn(pwmPin, HIGH);
    distance = (duration/2) / 74.676;
    lastTriggerTime = millis();
  }
  
 Serial.print("Pulse: ");
  Serial.println(Pulse);
  
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

if (millis() - lastLEDUpdateTime >= 1250) {
  if (distance == 0){
    // Red color
  fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
  FastLED.show();
  delay(1250); // Delay for half a second

  // Orange color
  fill_solid(leds, NUM_LEDS, CRGB(255, 102, 0));
  FastLED.show();
  delay(500); // Delay for half a second
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
    
      fill_solid(leds, NUM_LEDS, CRGB(246, 7, 250)); // Purple color
      FastLED.show();

    }
  else if (Mode == "Auto" && distance < 10) {
        fill_solid(leds, NUM_LEDS, CRGB(7, 246, 250)); // Cyan color
        FastLED.show();
  } else if (Mode == "game time" && distance > 10 ) {
    
      fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0)); // Red color
      FastLED.show();
  } else if (Mode == "game time" && distance < 10 && distance > 0) {
    fill_solid(leds, NUM_LEDS, CRGB(124,252,0)); 
    FastLED.show();
    delay(2);
  }
  lastLEDUpdateTime = millis();
}
}