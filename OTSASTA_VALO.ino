#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define relayPin D5 // Relay Pin

long duration, newDistance ; // Duration used to calculate distance
long distance = 99;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it. */
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 newDistance = duration/58.2;

 if (newDistance > 0 || newDistance < 100) {
  distance = newDistance;
  
  if (distance > 100) {
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println(" cm");
  }

  if (distance < 16) {
    digitalWrite(relayPin, HIGH);
    delay(250);
   } else {
    digitalWrite(relayPin, LOW);
   }
 }

 delay(250);
}