# 1 "C:\\2024-code\\LEDController\\LEDController.ino"
# 2 "C:\\2024-code\\LEDController\\LEDController.ino" 2






Adafruit_NeoPixel strip = Adafruit_NeoPixel(30 /* Number of NeoPixels*/, 6 /* Arduino pin connected to the NeoPixels.*/, ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/);

String Mode = "off"; // Set the initial mode to off.

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(9 /* Arduino pin tied to trigger pin on the ultrasonic sensor.*/, 0x1);
  pinMode(10 /* Arduino pin tied to echo pin on the ultrasonic sensor.*/, 0x0);
  Mode = "idle"; // Set the mode to idle.
}

void loop() {
  long duration, distance;
  digitalWrite(9 /* Arduino pin tied to trigger pin on the ultrasonic sensor.*/, 0x0);
  delayMicroseconds(2);
  digitalWrite(9 /* Arduino pin tied to trigger pin on the ultrasonic sensor.*/, 0x1);
  delayMicroseconds(10);
  digitalWrite(9 /* Arduino pin tied to trigger pin on the ultrasonic sensor.*/, 0x0);
  duration = pulseIn(10 /* Arduino pin tied to echo pin on the ultrasonic sensor.*/, 0x1);
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
