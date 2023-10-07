int photoPin = A0;
int signalPin = 3;
int photoValue;

void setup()
{
  pinMode(signalPin, OUTPUT);
  pinMode(photoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  photoValue = analogRead(photoPin);
  Serial.print("Sensor: ");
  Serial.println(photoValue);

  if (photoValue > 30) {
    digitalWrite(signalPin, HIGH);
  } else {
    digitalWrite(signalPin, LOW);
  }
}