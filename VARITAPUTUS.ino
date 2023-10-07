#include <FastLED.h>  
//#define DEBUG 1
#define LED_TYPE WS2812
#define NUM_LEDS 24
#define DATA_PIN_A A2
#define DATA_PIN_B A3
#define DATA_PIN_C A4
CRGB LEDS_A[NUM_LEDS];
CRGB LEDS_B[NUM_LEDS];
CRGB LEDS_C[NUM_LEDS];
int btn1 = 2;
bool buttonPressed = false;
int passSignal = 3;

int led1_state = 0;
int led1_stop = false;
int led2_state = 0;
int led2_stop = false;
int led3_state = 0;
int led3_stop = false;
int btn1_state = 0;
int passState = false;

unsigned long previousMillis = 0;  // Stores the last time the code was executed
unsigned long wait = 0;
unsigned long resetWait = 0;
const unsigned long interval = 600; // Interval in milliseconds

void setup() {
  pinMode(btn1, INPUT_PULLUP);
  pinMode(passSignal, OUTPUT);
  // Setup Serial Monitor
  Serial.begin(9600);
  // Add leds
  FastLED.addLeds<LED_TYPE, DATA_PIN_A, GRB>(LEDS_A, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_PIN_B, GRB>(LEDS_B, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_PIN_C, GRB>(LEDS_C, NUM_LEDS);
  // Turn off all LEDs
  FastLED.clear();
  FastLED.setBrightness(255);
}

void loop() {
  if (passState) {
    digitalWrite(passSignal, HIGH);
  } else {
  led1();
  led2();
  led3();
  btn1_state = digitalRead(btn1);
  unsigned long currentMillis = millis(); // Get the current time
  
  //Change colors in the leds
  if (currentMillis - previousMillis >= interval) {
    // Save the current time
    previousMillis = currentMillis;
    // Add +1 to led_state and led helper functions use a switch case to change color
    if (!led1_stop) {led1_state++;};
   	if (!led2_stop) {led2_state++;};
   	if (!led3_stop) {led3_state++;};
  }
  
  // If button is pressed
  if (btn1_state == 0) {
    resetWait = 100;
    
    if (!led1_stop) {
    	led1_stop = true;
        Serial.println("Led 1 stopped");
        Serial.print("Wait: ");
        Serial.println(wait);
        wait = 0;
    } else if (led1_stop && !led2_stop && wait > 150) {
    	led2_stop = true;
        Serial.println("Led 2 stopped");
        Serial.print("Wait: ");
        Serial.println(wait);
        wait = 0;
    } else if (led2_stop && wait > 150) {
    	led3_stop = true;
      	Serial.println("Led 3 stopped");
        Serial.print("Wait: ");
        Serial.println(wait);
        wait = 0;
    }
  }
  
  wait = wait + 1;
  
  if (resetWait >= 1) {
    resetWait = resetWait + 1;
    Serial.println(resetWait);
  };
  
  if (led1_stop && led2_stop && led3_stop && led1_state == 2 && led2_state == 2 && led3_state == 2) {
      Serial.print("Completed:");
      Serial.print(" led1_state: ");
      Serial.print(led1_state);
      Serial.print(", led2_state: ");
      Serial.print(led2_state);
      Serial.print(", led3_state: ");
      Serial.println(led3_state);
      passState = true;
  }
  
  if (resetWait >= 1000) {
      led1_stop = false;
      led2_stop = false;
      led3_stop = false;
      Serial.print("Reset. resetWait: ");
      Serial.println(resetWait);
      resetWait = 0;
  }
  
  delay(1);
  }
}

// LED HELPER FUNCTIONS

void led1() {
  if (led1_state > 4) {led1_state = 0;};
  switch (led1_state) {
  case 0:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::Aqua);
    FastLED.show();
    break;
  case 1:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::Yellow);
    FastLED.show();
    break;
  case 2:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::Green);
    FastLED.show();
    break;
  case 3:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::Red);
    FastLED.show();
    break;
  case 4:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::Purple);
    FastLED.show();
    break;
  default:
    fill_solid(LEDS_A, NUM_LEDS, CRGB::White);
    FastLED.show();
    break;
  }
}

void led2() {
  if (led2_state > 4) {led2_state = 0;};
  switch (led2_state) {
  case 0:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::Aqua);
    FastLED.show();
    break;
  case 1:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::Yellow);
    FastLED.show();
    break;
  case 2:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::Green);
    FastLED.show();
    break;
  case 3:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::Red);
    FastLED.show();
    break;
  case 4:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::Purple);
    FastLED.show();
    break;
  default:
    fill_solid(LEDS_B, NUM_LEDS, CRGB::White);
    FastLED.show();
    break;
  }
}

void led3() {
  if (led3_state > 4) {led3_state = 0;};
  switch (led3_state) {
  case 0:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::Aqua);
    FastLED.show();
    break;
  case 1:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::Yellow);
    FastLED.show();
    break;
  case 2:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::Green);
    FastLED.show();
    break;
  case 3:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::Red);
    FastLED.show();
    break;
  case 4:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::Purple);
    FastLED.show();
    break;
  default:
    fill_solid(LEDS_C, NUM_LEDS, CRGB::White);
    FastLED.show();
    break;
  }
}