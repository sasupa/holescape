/* READ THIS TUTORIAL WHEN USING THE WEBSERVER: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

// Set WiFi credentials
#define WIFI_SSID "Cirko Guest"
#define WIFI_PASS ""
// Kotiboksi_J7FB_5G / G86XXCGBENNUS

int sensorPin = A0;
int relayPin = D6;

// Set up Upd for OSC commands to QLab
WiFiUDP Udp;
unsigned int localUdpPort = 4220;
char incomingPacket[256];

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);

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
}

void loop() {
    // Current voltage value is measured...
    int rawValue = analogRead(sensorPin);
    float voltage = rawValue * (5.0/1023) * 1000;
    float resitance = 10000 * ( voltage / ( 5000.0 - voltage) ); 
    // ... and here output to the serial interface
    Serial.print("Voltage value:"); Serial.println(voltage);
 
    if (voltage < 4800) {
      digitalWrite(relayPin, HIGH);
      Udp.beginPacket("10.254.187.232", 53535);
      Udp.write("/cue/1/start");
      Udp.endPacket();
      Serial.println("cue 1 go");
    } else {
      digitalWrite(relayPin, LOW);
      Udp.beginPacket("10.254.187.232", 53535);
      Udp.write("/cue/1/stop");
      Udp.endPacket();
      Serial.println("cue 1 stop");
    }
    delay(500);

  /*
  Udp.beginPacket("172.20.10.3", 53535);
  Udp.write("/cue/1/start");
  Udp.endPacket();
  Serial.println("cue 1 go");
  delay(1000);

  Udp.beginPacket("172.20.10.3", 53535);
  Udp.write("/cue/1/stop");
  Udp.endPacket();
  Serial.println("cue 1 stop");
  delay(1000);

  Udp.beginPacket("172.20.10.3, 10.8.55.161", 53535);
  Udp.write("/cue/2/start");
  Udp.endPacket();
  Serial.println("cue 2 start");
  delay(1000);

  Udp.beginPacket("172.20.10.3, 10.8.55.161", 53535);
  Udp.write("/cue/2/stop");
  Udp.endPacket();
  Serial.println("cue 2 stop");

  delay(1000);
  */
}