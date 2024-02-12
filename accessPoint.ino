/*
The Illumina API Project is based on an Arduino Uno 3R and a Generic ESP8266 Module.
It aims to provide a solution for remotely controlling lights or illumination through a smartphone by local webSite via WiFi of ESP8266 (Access Point).
However, please note that this is only a prototype and not a commercial product.

If you encounter any issues, please do not hesitate to reach out to us for assistance.

/!\ Independent Study Project's Prototype Only /!\
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

// // // // // Setup Access Point // // // // //
String ssid = "Smart Bamboo Lamp"; // SSID Name
String password = "12345678"; // Password of Access Point
ESP8266WebServer server(80); // Web Server Port

// // // // // Setup WebSocket // // // // //
WebSocketsServer webSockets(81); // WebSocket Port

// // // // // Relay Path // // // // //
String r1n = "1";
String r1f = "0";

// // // // // Setup Variable // // // // //
const int ledPin = 2;
bool lightState = false;


// Web Root
void handleRoot() {
  String content = "<!DOCTYPE html><html lang=\"en\"><head><link href='https://fonts.googleapis.com/css?family=Kanit' rel='stylesheet'><meta name=\"viewport\" content=\"width=1024\"><meta charset=\"UTF-8\"><title>Smart Bamboo Lamp</title><style>* {font-family: kanit;}*::-webkit-scrollbar {display: none;}body, html {overflow: hidden;margin: 0;padding: 0;width: 100%;height: 100%;}.container {display: flex;justify-content: center;align-items: center;}a.on {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(120, 100%, 35%);transition: 0.3s ease;text-decoration: none;}a.off {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(0, 100%, 50%);transition: 0.3s ease;text-decoration: none;}a.on:hover {background: hsl(120, 100%, 35%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a.off:hover {background: hsl(0, 100%, 50%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a {font-size: 75pt;top: 225pt;}</style></head><body><div class=\"container hidden\">";

  if (lightState) {
    content += "<a href=\"turnOff\" style=\"max-width: 100%;max-height: 100%; left: 25px\" class=\"off\">Turn Off</a>";
  } else {
    content += "<a href=\"turnOn\" style=\"max-width: 100%;max-height: 100%; right: 25px\" class=\"on\">Turn On</a>";
  }

  content += "</div></body><script>";
  content += "var webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');";
  content += "webSocket.onmessage = function(event) {";
  content += "  if (event.data === '1') {";
  content += "    document.querySelector('.on').style.display = 'none';";
  content += "    document.querySelector('.off').style.display = 'inline-block';";
  content += "  } else if (event.data === '0') {";
  content += "    document.querySelector('.off').style.display = 'none';";
  content += "    document.querySelector('.on').style.display = 'inline-block';";
  content += "  }";
  content += "};";
  content += "function turnOn() { fetch('/turnOn'); }";
  content += "function turnOff() { fetch('/turnOff'); }";
  content += "</script></html>";

  server.send(200, "text/html", content);
}

// // // // // WebSockets Recevier // // // // //
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      if (length == 1 && payload[0] == '1') {
        lightState = true;
      } else if (length == 1 && payload[0] == '0') {
        lightState = false;
      }
      webSockets.broadcastTXT(lightState ? "1" : "0");
      break;
  }
}

// // // // // handle Turn On & Turn Off // // // // //
void handleTurnOn() {
  digitalWrite(ledPin, LOW);
  lightState = true;
  Serial.write(r1n.c_str(), r1n.length());

  String content = "<!DOCTYPE html><html lang=\"en\"><head><link href='https://fonts.googleapis.com/css?family=Kanit' rel='stylesheet'><meta name=\"viewport\" content=\"width=1024\"><meta charset=\"UTF-8\"><title>Smart Bamboo Lamp</title><style>* {font-family: kanit;}*::-webkit-scrollbar {display: none;}body, html {overflow: hidden;margin: 0;padding: 0;width: 100%;height: 100%;}.container {display: flex;justify-content: center;align-items: center;}a.on {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(120, 100%, 35%);transition: 0.3s ease;text-decoration: none;}a.off {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(0, 100%, 50%);transition: 0.3s ease;text-decoration: none;}a.on:hover {background: hsl(120, 100%, 35%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a.off:hover {background: hsl(0, 100%, 50%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a {font-size: 75pt;top: 225pt;}</style></head><body><div class=\"container hidden\">";

  if (lightState) {
    content += "<a href=\"turnOff\" style=\"max-width: 100%;max-height: 100%; left: 25px\" class=\"off\">Turn Off</a>";
  } else {
    content += "<a href=\"turnOn\" style=\"max-width: 100%;max-height: 100%; right: 25px\" class=\"on\">Turn On</a>";
  }

  content += "</div></body><script>";
  content += "var webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');";
  content += "webSocket.onmessage = function(event) {";
  content += "  if (event.data === '1') {";
  content += "    document.querySelector('.on').style.display = 'none';";
  content += "    document.querySelector('.off').style.display = 'inline-block';";
  content += "  } else if (event.data === '0') {";
  content += "    document.querySelector('.off').style.display = 'none';";
  content += "    document.querySelector('.on').style.display = 'inline-block';";
  content += "  }";
  content += "};";
  content += "function turnOn() { fetch('/turnOn'); }";
  content += "function turnOff() { fetch('/turnOff'); }";
  content += "</script></html>";

  server.send(200, "text/html", content);
  digitalWrite(ledPin, HIGH);
}

void handleTurnOff() {
  digitalWrite(ledPin, LOW);
  lightState = false;
  Serial.write(r1f.c_str(), r1n.length());

  String content = "<!DOCTYPE html><html lang=\"en\"><head><link href='https://fonts.googleapis.com/css?family=Kanit' rel='stylesheet'><meta name=\"viewport\" content=\"width=1024\"><meta charset=\"UTF-8\"><title>Smart Bamboo Lamp</title><style>* {font-family: kanit;}*::-webkit-scrollbar {display: none;}body, html {overflow: hidden;margin: 0;padding: 0;width: 100%;height: 100%;}.container {display: flex;justify-content: center;align-items: center;}a.on {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(120, 100%, 35%);transition: 0.3s ease;text-decoration: none;}a.off {position: relative;display: inline-block;padding: 0.5rem 1rem;color: black;border-radius: 50px;border: 2px solid hsl(0, 100%, 50%);transition: 0.3s ease;text-decoration: none;}a.on:hover {background: hsl(120, 100%, 35%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a.off:hover {background: hsl(0, 100%, 50%);color: white;transform: translateY(-5px);opacity: initial;box-shadow: 3px 3px 10px rgba(0,0,0,0.4);}a {font-size: 75pt;top: 225pt;}</style></head><body><div class=\"container hidden\">";

  if (lightState) {
    content += "<a href=\"turnOff\" style=\"max-width: 100%;max-height: 100%; left: 25px\" class=\"off\">Turn Off</a>";
  } else {
    content += "<a href=\"turnOn\" style=\"max-width: 100%;max-height: 100%; right: 25px\" class=\"on\">Turn On</a>";
  }

  content += "</div></body><script>";
  content += "var webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');";
  content += "webSocket.onmessage = function(event) {";
  content += "  if (event.data === '1') {";
  content += "    document.querySelector('.on').style.display = 'none';";
  content += "    document.querySelector('.off').style.display = 'inline-block';";
  content += "  } else if (event.data === '0') {";
  content += "    document.querySelector('.off').style.display = 'none';";
  content += "    document.querySelector('.on').style.display = 'inline-block';";
  content += "  }";
  content += "};";
  content += "function turnOn() { fetch('/turnOn'); }";
  content += "function turnOff() { fetch('/turnOff'); }";
  content += "</script></html>";

  server.send(200, "text/html", content);
  digitalWrite(ledPin, HIGH);
}


// Setup System
void setup() {
  Serial.begin(115200);

  if (password.length() < 8) {
    Serial.println("Password must be at least 8 characters long.");
    exit(1);
  }

  pinMode(ledPin, OUTPUT); // Setup LedPin
  digitalWrite(ledPin, LOW);
  WiFi.mode(WIFI_AP); // Changes WiFi Status to "Access Point" instead.
  WiFi.softAP(ssid, password); // set SSID and Password to Access Point.
  server.on("/", HTTP_GET, handleRoot);
  server.on("/turnOn", HTTP_GET, handleTurnOn);
  server.on("/turnOff", HTTP_GET, handleTurnOff);
  server.begin();
  delay(1);
  digitalWrite(ledPin, HIGH);
}

// Loop System
void loop() {
  server.handleClient();
  int numStations = WiFi.softAPgetStationNum();
}
