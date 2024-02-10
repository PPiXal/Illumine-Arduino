#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h> // Include the WebSocket library

// Define WiFi credentials
const char* ssid = "Smart Bamboo Lamp";
const char* password = "12345678";

ESP8266WebServer server(80);
WebSocketsServer webSocket(81); // Create a WebSocket server on port 81

bool lampState = false;

void handleRoot() {
  String content = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><title>Smart Bamboo Lamp</title></head><body>";
  
  if (lampState) {
    content += "<button onclick=\"turnOff()\">Turn Off</button>";
  } else {
    content += "<button onclick=\"turnOn()\">Turn On</button>";
  }

  content += "<script>var socket = new WebSocket('ws://" + WiFi.softAPIP().toString() + ":81/');";
  content += "socket.onmessage = function(event) { if(event.data === '1') document.querySelector('button').innerText = 'Turn Off'; else document.querySelector('button').innerText = 'Turn On'; };";
  content += "function turnOn() { socket.send('1'); } function turnOff() { socket.send('0'); }</script></body></html>";

  server.send(200, "text/html", content);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_TEXT:
      if (length == 1 && payload[0] == '1') {
        lampState = true;
      } else if (length == 1 && payload[0] == '0') {
        lampState = false;
      }
      webSocket.broadcastTXT(lampState ? "1" : "0"); // Broadcast the updated lamp state to all clients
      break;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  // Serial.print("AP IP address: ");
  // Serial.println(WiFi.softAPIP());

  // Setup the HTTP server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();

  // Setup the WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();
}
