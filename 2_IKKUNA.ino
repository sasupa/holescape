//
//    FILE: HX_calibration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/HX711

#include "HX711.h"
HX711 myScale;

uint8_t dataPin = 6;
uint8_t clockPin = 7;
int relayOne = 3;
int relayTwo = 4;
bool actuatorUp = false;
uint32_t start, stop;
volatile float f;

//declare variables for the motor pins
int motorPin1 = 8; // Blue - 28BYJ48 pin 1
int motorPin2 = 9; // Pink - 28BYJ48 pin 2
int motorPin3 = 10; // Yellow - 28BYJ48 pin 3
int motorPin4 = 11; // Orange - 28BYJ48 pin 4
int motorSpeed = 1200; //variable to set stepper speed
int count = 0; // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup()
{
  // Motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  myScale.begin(dataPin, clockPin);
  //calibrate(); Ei tarvita nyt, koska kun calibroit ukerran tiedetään että: use scale.set_offset(4294902779); and scale.set_scale(-495.288879);
  myScale.set_offset(4294902779);
  myScale.set_scale(-495.288879);

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  digitalWrite(relayOne, HIGH);
  digitalWrite(relayTwo, HIGH);
}

void loop() {
  // Read the weight from the sensor
  int weight = myScale.get_units();

  // Print the weight value
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" grams");

  delay(100);
  /*

  // YLÖS
   digitalWrite(relayOne, LOW);
   digitalWrite(relayTwo, HIGH);
   delay(8000);
   
   // POIS
   digitalWrite(relayOne, LOW);
   digitalWrite(relayTwo, LOW);
   delay(8000);

// ALAS
   digitalWrite(relayOne, HIGH);
   digitalWrite(relayTwo, LOW);
   delay(8000);

    
   delay(1000);
   digitalWrite(relayOne, LOW);
   digitalWrite(relayTwo, HIGH);
   delay(1000);
   digitalWrite(relayOne, LOW);
   digitalWrite(relayTwo, LOW);
   delay(1000);

 
  ALKUP KOODI ALKAA

  anticlockwise();
  Serial.print("Count: ");
  Serial.println(count);

  // Read the weight from the sensor
  int weight = myScale.get_units();

  // Print the weight value
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" grams");

  // If weight on scale, turn linear actuator on
  if (weight > 50) {
    if (actuatorUp) {
      digitalWrite(relayOne, LOW);
      digitalWrite(relayTwo, LOW);
    } else {
      digitalWrite(relayOne, LOW);
      digitalWrite(relayTwo, HIGH);
      delay(8000); // EI RIITÄ?
      actuatorUp = true;
    }
  } else {
    if (actuatorUp) {
      digitalWrite(relayOne, HIGH);
      digitalWrite(relayTwo, LOW);
      delay(15000); // EI RIITÄ?
      actuatorUp = false;
    }
    digitalWrite(relayOne, LOW);
    digitalWrite(relayTwo, LOW);
  }

  delay(0); // Wait for 1 second
}

void anticlockwise() {
 for (int i = 0; i < 8; i++) {
  setOutput(i);
  delayMicroseconds(motorSpeed);
 }
}

void clockwise() {
 for (int i = 7; i >= 0; i--) {
  setOutput(i);
  delayMicroseconds(motorSpeed);
 }
}

void setOutput(int out)
{
 digitalWrite(motorPin1, bitRead(lookup[out], 0));
 digitalWrite(motorPin2, bitRead(lookup[out], 1));
 digitalWrite(motorPin3, bitRead(lookup[out], 2));
 digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

// VAA'AN KALIBROINTI
void calibrate()
{
  Serial.println("\n\nCALIBRATION\n===========");
  Serial.println("remove all weight from the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("and press enter\n");
  while (Serial.available() == 0);

  Serial.println("Determine zero weight offset");
  myScale.tare(20);  // average 20 measurements.
  uint32_t offset = myScale.get_offset();

  Serial.print("OFFSET: ");
  Serial.println(offset);
  Serial.println();


  Serial.println("place a weight on the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("enter the weight in (whole) grams and press enter");
  uint32_t weight = 0;
  while (Serial.peek() != '\n')
  {
    if (Serial.available())
    {
      char ch = Serial.read();
      if (isdigit(ch))
      {
        weight *= 10;
        weight = weight + (ch - '0');
      }
    }
  }
  Serial.print("WEIGHT: ");
  Serial.println(weight);
  myScale.calibrate_scale(weight, 20);
  float scale = myScale.get_scale();

  Serial.print("SCALE:  ");
  Serial.println(scale, 6);

  Serial.print("\nuse scale.set_offset(");
  Serial.print(offset);
  Serial.print("); and scale.set_scale(");
  Serial.print(scale, 6);
  Serial.print(");\n");
  Serial.println("in the setup of your project");

  Serial.println("\n\n");

  ALKUP KOODI LOPPUU
  */
}