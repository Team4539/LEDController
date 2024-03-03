#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 9 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define B_PIN 10  // Arduino pin connected to the B wire.
#define NUM_LEDS 45 // Number of NeoPixels
#define pwmPinSnd  3 // Change this to the pin you've connected the PWM signal to
#define pwmPinRcv 5 // Change this to the pin you've connected the PWM signal to




String Mode = "game time"; // Set the initial mode to off.
int Pulse; 
int SND;
int dutyCycle = 128; // Set the initial duty cycle to 50%.
unsigned long startTime = millis(); // get the start time
unsigned long runTime = 30000;
int delayTime = 30000 / (3 * NUM_LEDS); 

CRGB leds[NUM_LEDS]; // Declare the 'leds' array before calling the 'FastLED.addLeds' function.

void setup() {
  
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, B_PIN, RGB>(leds, NUM_LEDS);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pwmPinRcv, INPUT);
  pinMode(pwmPinSnd, OUTPUT);
  analogWrite(pwmPinSnd, 0);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  int delayTime = 30000 / (3 * NUM_LEDS); // Total duration is 30000 milliseconds

  int meetPoint = NUM_LEDS / 2;
  for(int i = 0; i <= meetPoint; i++) {
    leds[i] = CRGB(255, 102, 0);
    leds[NUM_LEDS - 1 - i] = CRGB(37, 150, 190);
    FastLED.show();
    delay(delayTime);
  }

  for(int i = 0; i <= meetPoint; i++) {
    leds[meetPoint - i] = CRGB::White;
    leds[meetPoint + i] = CRGB::White;
    FastLED.show();
    delay(delayTime);

    for(int j = 0; j < NUM_LEDS; j++) {
      if(j % 8 < 4) {
        leds[j] = CRGB(255, 102, 0); 
      } else {
        leds[j] = CRGB(37, 150, 190); 
      }
    }
    FastLED.show();
  }
}


void loop() {
  static unsigned long lastTriggerTime = 0;
  static unsigned long lastLEDUpdateTime = 0;
  long duration, distance;
  Pulse = pulseIn(pwmPinRcv, HIGH);

  if (millis() - lastTriggerTime >= 1) {
    digitalWrite(TRIGGER_PIN, LOW);  
    delayMicroseconds(1); 
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(1); 
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration/2) / 74.676;
    lastTriggerTime = millis();
  }
  
 Serial.print("Pulse: ");
  Serial.println(Pulse);
  
  Serial.print("Distance: ");
  Serial.println(distance); 
  Serial.print(" inches");

if (Pulse <= 100){
  Mode = "Idle";
} else if (Pulse > 1900 && Pulse <= 2100){
  Mode = "Auto";
}else {
  Mode = "game time";
} 
 Serial.print("Mode: ");
  Serial.println(Mode);
  Serial.println(" ");

    if (distance == 0){
    // Red color
  fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
  FastLED.show();
  analogWrite(pwmPinSnd, 0);
  delay(1250); // Delay for half a second

  // Orange color
  fill_solid(leds, NUM_LEDS, CRGB(255, 102, 0));
  FastLED.show();
  analogWrite(pwmPinSnd, 255);
  delay(500); // Delay for half a second
  }
  else if (Mode == "Idle") {
    for(int i=0; i < NUM_LEDS ; i++) {
      if(i % 8 < 4) {
        leds[i] = CRGB(255, 102, 0); //safety orange (Kaotic main color)
      } else {
        leds[i] = CRGB(37, 150, 190); // Eastern blue color (Kaotic secondary color)
      }
      FastLED.show();
      analogWrite(pwmPinSnd, 255);
    }
  } else if (Mode == "Auto" && distance > 10) {
    
      fill_solid(leds, NUM_LEDS, CRGB(246, 7, 250)); // Purple color
      FastLED.show();
      analogWrite(pwmPinSnd, 0);
   }
  else if (Mode == "Auto" && distance < 10) {
        fill_solid(leds, NUM_LEDS, CRGB(7, 246, 250)); // Cyan color
        FastLED.show();
        analogWrite(pwmPinSnd, 255);

  } else if (Mode == "game time" && distance > 10 ) {
    
      fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0)); // Red color
      FastLED.show();
      analogWrite(pwmPinSnd, 0);
  } else if (Mode == "game time" && distance < 10 && distance > 0) {
    fill_solid(leds, NUM_LEDS, CRGB(124,252,0)); 
    FastLED.show();
    analogWrite(pwmPinSnd, 255);
  }
}
