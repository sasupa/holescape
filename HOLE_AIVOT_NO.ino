/* READ THIS TUTORIAL WHEN USING THE WEBSERVER: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer */

// TÄMÄ ON Normally Open (NO) kortti, QLAB iskut 1-4
// Tällä ohjataan toisia arduinoja päälle ja kaappilukkoja tms

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

// Set WiFi credentials
#define WIFI_SSID "5GCPE_99DB24"
#define WIFI_PASS "5DP2J42F65"
#define QLAB_IP "192.168.100.158"
// HOLE: 5GCPE_99DB24 / 5DP2J42F65
// Sasun koti: Kotiboksi_J7FB_5G / G86XXCGBENNUS

int sensorPin1 = D5;
int sensorPin2 = D6;
int sensorPin3 = D7;
int sensorPin4 = A0;
int relayPin1 = D0;
int relayPin2 = D1;
int relayPin3 = D3;
int relayPin4 = D2;
int sensorPin1Val;
int sensorPin2Val;
int sensorPin3Val;
int sensorPin4Val;
bool sensorPin1State = false;
bool sensorPin2State = false;
bool sensorPin3State = false;
bool sensorPin4State = false;

// Set up Upd for OSC commands to QLab
WiFiUDP Udp;
unsigned int localUdpPort = 4220;
char incomingPacket[256];

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Udp.begin(localUdpPort);
  Serial.println("Listening to Udp");

  // Some pins boot high, just to make sure all are closed
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin1, LOW);
}

void loop() {
    sensorPin1Val = digitalRead(sensorPin1);
    sensorPin2Val = analogRead(sensorPin2);
    sensorPin3Val = digitalRead(sensorPin3);
    sensorPin4Val = analogRead(sensorPin4);

    Serial.print("Sensor1: ");
    Serial.print(sensorPin1Val);
    Serial.print(" | Sensor2: ");
    Serial.print(sensorPin2Val);
    Serial.print(" | Sensor3: ");
    Serial.print(sensorPin3Val);
    Serial.print(" | Sensor4: ");
    Serial.println(sensorPin4Val);
    delay(500);

    if (sensorPin1Val == 1 && !sensorPin1State) {
      sensorPin1State = true;
      digitalWrite(relayPin1, HIGH);
      Udp.beginPacket(QLAB_IP, 53535);
      Udp.write("/cue/1/start");
      Udp.endPacket();
      Serial.println("Relay 1 ON = POWER ON / CUE 1 GO");
      delay(1000);
      digitalWrite(relayPin1, LOW);
      Serial.println("Relay 1 ON = POWER OFF");
    }

    if (sensorPin2Val > 100 && !sensorPin2State) {
      sensorPin2State = true;
      digitalWrite(relayPin2, HIGH);
      Udp.beginPacket(QLAB_IP, 53535);
      Udp.write("/cue/2/start");
      Udp.endPacket();
      Serial.println("Relay 2 ON = POWER ON / CUE 2 GO");
      delay(1000);
      digitalWrite(relayPin2, LOW);
      Serial.println("Relay 2 ON = POWER OFF");
    }

    if (sensorPin3Val == 1 && !sensorPin3State) {
      sensorPin3State = true;
      digitalWrite(relayPin3, HIGH);
      Udp.beginPacket(QLAB_IP, 53535);
      Udp.write("/cue/3/start");
      Udp.endPacket();
      Serial.println("Relay 3 ON = POWER ON / CUE 3 GO");
      delay(1000);
      digitalWrite(relayPin3, LOW);
      Serial.println("Relay 3 ON = POWER OFF");
    }

    if (sensorPin4Val > 100 && !sensorPin4State) {
      sensorPin4State = true;
      digitalWrite(relayPin4, HIGH);
      Udp.beginPacket(QLAB_IP, 53535);
      Udp.write("/cue/4/start");
      Udp.endPacket();
      Serial.println("Relay 4 ON = POWER ON / CUE 4 GO");
      delay(1000);
      digitalWrite(relayPin4, LOW);
      Serial.println("Relay 4 ON = POWER OFF");
    }
}