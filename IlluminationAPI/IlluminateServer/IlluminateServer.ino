#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

String ssid = "Smart Bamboo Lamp"; // Put your SSID from wifi route or your Hotspot
String password = "12345678"; // Put your Password from wifi route or your Hotspot
ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

String r1n = "1";
String r1f = "0";

const int ledPin = 2;
bool lightState = false;

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
}

void handleTurnOff() {
  digitalWrite(ledPin, HIGH);
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
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  server.on("/", HTTP_GET, handleRoot);
  server.on("/turnOn", HTTP_GET, handleTurnOn);
  server.on("/turnOff", HTTP_GET, handleTurnOff);
  server.begin();
  delay(1);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  server.handleClient();
  int numStations = WiFi.softAPgetStationNum();
  // if (lightState) {
  //   Serial.write(r1n.c_str(), r1n.length());
  // } else if (!lightState) {
  //   Serial.write(r1f.c_str(), r1f.length());
  // }
}
