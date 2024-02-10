#include <SoftwareSerial.h>

SoftwareSerial espSerial(3, 2); // RX, TX
const int relayPin[4] = {11,10,9,8};
const int ledPin = 13;

int IN(int index) {
  return index - 1;
}

// relaysPort:turnBool
String r1n = "1";
String r1f = "0";


void setup() {
  pinMode(relayPin[IN(1)], OUTPUT);
  pinMode(relayPin[IN(2)], OUTPUT);
  pinMode(relayPin[IN(3)], OUTPUT);
  pinMode(relayPin[IN(4)], OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // // Turn Off All light bulb
  digitalWrite(relayPin[IN(1)], HIGH);
  digitalWrite(relayPin[IN(2)], HIGH);
  digitalWrite(relayPin[IN(3)], HIGH);
  digitalWrite(relayPin[IN(4)], HIGH);

  Serial.begin(9600); // Debugger only
  espSerial.begin(115200); // Received data from ESP8266 module
}

void loop() {
  // Check for incoming data from the ESP8266
  if (espSerial.available() > 0) {
    String state = espSerial.readStringUntil('\n');
    Serial.println(state);
    if (state == r1n) {
      digitalWrite(ledPin, LOW); // Turn on LED for indication
      digitalWrite(relayPin[IN(1)], LOW); // Turn the relay on to turn the light bulb on
    }
    else if (state == r1f) {
      digitalWrite(ledPin, HIGH); // Turn off LED for indication
      digitalWrite(relayPin[IN(1)], HIGH); // Turn the relay off to turn the light bulb off
    }

    // else if (state == r2n) {
    //   digitalWrite(relayPin[IN(2)], LOW); // Turn the relay on to turn the light bulb on
    // }
    // else if (state == r2f) {
    //   digitalWrite(relayPin[IN(2)], HIGH); // Turn the relay off to turn the light bulb off
    // }

    // else if (state == r3n) {
    //   digitalWrite(relayPin[IN(3)], LOW); // Turn the relay on to turn the light bulb on
    // }
    // else if (state == r3f) {
    //   digitalWrite(relayPin[IN(3)], HIGH); // Turn the relay off to turn the light bulb off
    // }

    // else if (state == r4n) {
    //   digitalWrite(relayPin[IN(4)], LOW); // Turn the relay on to turn the light bulb on
    // }
    // else if (state == r4f) {
    //   digitalWrite(relayPin[IN(4)], HIGH); // Turn the relay off to turn the light bulb off
    // }
  }
}