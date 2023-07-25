/* READ THIS TUTORIAL WHEN USING THE WEBSERVER: https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Simpletimer.h>
#include "Handlers.h"

// the timer object
Simpletimer timer1{};

// Set WiFi credentials
#define WIFI_SSID "Kotiboksi_J7FB"
#define WIFI_PASS "G86XXCGBENNUS"
// Kotiboksi_J7FB_5G / G86XXCGBENNUS

// Define the task and relay pins
#define relayPin1 D8
#define taskPin1 A0
int taskValue1 = 0;

// Create a new web server
ESP8266WebServer webserver(80);

// Set up Upd for OSC commands to QLab
WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[256];

// Handlers
void handleRoot() {
  for (int i = 0; i < webserver.args(); i++) {
    Serial.print(webserver.argName(i));
    Serial.print(": ");
    Serial.println(webserver.arg(i));
  } 
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  StreamString temp;
  temp.reserve(500);  // Preallocate a large chunk to avoid memory fragmentation
  temp.printf("\
<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>HOLE</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>HOLE AIVOT v0.1</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <br>\
    <p>Task 1: %04d </p><a href='/inline'>FIRE</a>\
    <p>Task 2: %04d </p><a href='/inline'>FIRE</a>\
    <p>Task 3: %04d </p><a href='/inline'>FIRE</a>\
    <p>Task 4: %04d </p><a href='/inline'>FIRE</a>\
  </body>\
</html>",
              hr, min % 60, sec % 60, taskValue1, taskValue1, taskValue1, taskValue1);
  webserver.send(200, "text/html", temp.c_str());
}

// Handle 404
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webserver.uri();
  message += "\nMethod: ";
  message += (webserver.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webserver.args();
  message += "\n";
  for (uint8_t i = 0; i < webserver.args(); i++) { message += " " + webserver.argName(i) + ": " + webserver.arg(i) + "\n"; }
  webserver.send(404, "text/plain", message);
}

void taskChecker() {
  taskValue1 = analogRead(taskPin1);
  if (taskValue1 > 1000) {digitalWrite(relayPin1, HIGH);} else {digitalWrite(relayPin1, LOW);}
}

void setup() {
  // Setup serial port
  Serial.begin(115200);
  timer1.register_callback(taskChecker);
  Serial.println();

  // Set pin modes and boot relays
  pinMode(relayPin1, OUTPUT);
  pinMode(taskPin1, INPUT);

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

  // Start Web Server
  webserver.on("/", handleRoot);
  webserver.on("/inline", []() {
    webserver.send(200, "text/plain", "this works as well");
  });
  webserver.onNotFound(handleNotFound);
  webserver.begin();
  Serial.println("HTTP server started");
}

void loop() {
  timer1.run(100);
  webserver.handleClient();
  /*
  int taskValue1 = analogRead(taskPin1);
  if (taskValue1 > 1000) {digitalWrite(relayPin1, HIGH);} else {digitalWrite(relayPin1, LOW);}

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

  Udp.beginPacket("172.20.10.3", 53535);
  Udp.write("/cue/2/start");
  Udp.endPacket();
  Serial.println("cue 2 start");
  delay(1000);

  Udp.beginPacket("172.20.10.3", 53535);
  Udp.write("/cue/2/stop");
  Udp.endPacket();
  Serial.println("cue 2 stop");

  delay(1000);
  */
}