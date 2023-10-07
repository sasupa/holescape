int motorPin = 6;
int photoPin = A0;
int signalPin = 3;
int photoValue;
int wait = 0;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(signalPin, OUTPUT);
  pinMode(photoPin, INPUT);
  digitalWrite(motorPin, LOW);
  Serial.begin(9600);
}

void loop() {
  photoValue = analogRead(photoPin);
  Serial.print("Sensor: ");
  Serial.println(photoValue);

  if (photoValue > 3) {
  	digitalWrite(motorPin, HIGH);
    digitalWrite(signalPin, HIGH);
  } else {
    wait++;
    Serial.print("Wait: ");
    Serial.println(wait);
  }
  
  //Change colors in the leds
  if (wait > 200) {
    digitalWrite(motorPin, LOW);
    digitalWrite(signalPin, LOW);
    wait = 0;
  }
  delay(50);
}