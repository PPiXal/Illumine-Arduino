/*
The Illumina Project is based on an Arduino Uno 3R and a Generic ESP8266 Module.
It aims to provide a solution for remotely controlling lights or illumination through a smartphone by local webSite via WiFi.
However, please note that this is only a prototype and not a commercial product.

If you encounter any issues, please do not hesitate to reach out to us for assistance.
*/

#include <ESP8266WiFi.h>

String ssid = "YourSSID"; // Put your SSID from wifi route or your Hotspot
String password = "YourPassword"; // Put your Password from wifi route or your Hotspot
WiFiServer server(80); // Set Server at Port 80

// getPins & statePin
const int ledPin = 2;

// relaysPort:turnBool
String r1n = "1:1";
String r1f = "0:1";
String r2n = "1:2";
String r2f = "0:2";
String r3n = "1:3";
String r3f = "0:3";
String r4n = "1:4";
String r4f = "0:4";

void __preload() {
  Serial.begin(115200); // Sent data from ESP8266 module & Received data from Python Signal Application 
  
  // ResetPinMode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Settings WiFi Module
  WiFi.setAutoReconnect(true);
}

bool recon_t() {
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  return true;
}

void handleRoot(WiFiClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>Illumination.API</title></head>");
  client.println("<body>");
  client.println("<h1>Light Bulb Control</h1>");
  client.println("<h3>Relay 1</h3>");
  client.println("<p><a href=\"/state=on?port=1\">Turn On</a></p>");
  client.println("<p><a href=\"/state=off?port=1\">Turn Off</a></p>");
  client.println("<h3>Relay 2</h3>");
  client.println("<p><a href=\"/state=on?port=2\">Turn On</a></p>");
  client.println("<p><a href=\"/state=off?port=2\">Turn Off</a></p>");
  client.println("<h3>Relay 3</h3>");
  client.println("<p><a href=\"/state=on?port=3\">Turn On</a></p>");
  client.println("<p><a href=\"/state=off?port=3\">Turn Off</a></p>");
  client.println("<h3>Relay 4</h3>");
  client.println("<p><a href=\"/state=on?port=4\">Turn On</a></p>");
  client.println("<p><a href=\"/state=off?port=4\">Turn Off</a></p>");
  client.println("<footer> Illumination.API version 1.2.4-build | Powered by ESP8266 WiFi Board </footer>");
  client.println("</body>");
  client.println("</html>");
}

void handleIlluminateState(WiFiClient client, String request) {
  digitalWrite(ledPin, LOW);
  if (request.indexOf("/state=on?port=1") != -1) {
    Serial.write(r1n.c_str(), r1n.length());

  } else if (request.indexOf("/state=off?port=1") != -1) {
    Serial.write(r1f.c_str(), r1f.length());
    client.println("");
  }

  else if (request.indexOf("/state=on?port=2") != -1) {
    Serial.write(r2n.c_str(), r2n.length());
    client.println("");
  } else if (request.indexOf("/state=off?port=2") != -1) {
    Serial.write(r2f.c_str(), r2f.length());
    client.println("");
  }

  else if (request.indexOf("/state=on?port=3") != -1) {
    Serial.write(r3n.c_str(), r3n.length());
    client.println("");
  } else if (request.indexOf("/state=off?port=3") != -1) {
    Serial.write(r3f.c_str(), r3f.length());
    client.println("");
  }

  else if (request.indexOf("/state=on?port=4") != -1) {
    Serial.write(r4n.c_str(), r4n.length());
    client.println("");
  } else if (request.indexOf("/state=off?port=4") != -1) {
    Serial.write(r4f.c_str(), r4f.length());
    client.println("");
  }
  
  else {
    client.println("HTTP/1.1 400 Bad Request");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<h1>400 Bad Request</h1>");
  }
  digitalWrite(ledPin, HIGH);
}

void setup() {
  __preload();
  
  WiFi.begin(ssid, password);
  bool con_suc = recon_t();
  if (con_suc) {
    server.begin();
  }
  else setup();
}

void loop() {
  if (!WiFi.isConnected()) {
    WiFi.reconnect();
    bool con_suc = recon_t();
    if (con_suc) {
      server.begin();
    }
  }

  // function Server activation below. 
  digitalWrite(ledPin, LOW);
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    handleRoot(client);
    handleIlluminateState(client, request);

    delay(1);
    client.stop();
  }
}
