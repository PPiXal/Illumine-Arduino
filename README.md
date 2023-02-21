<h1>IlluminateAPI::Light Controller via smartphone over WiFi</h1>
This project shows how to use an Arduino Uno R3 and an ESP8266 WiFi board to turn on/off a light remotely using a mobile app or a web browser.

**<h2>Hardware</h2>**
 - Arduino Uno R3
 - ESP8266 WiFi board
 - Relay module
 - AC to DC power supply
 - Jumper wires
 - light bulb

**<h2>Software</h2>**
 - Arduino IDE
 - Blynk app (for mobile) or web browser
 - WiFi network

**<h2>SetUp</h2>**
1. Connect the **ESP8266 WiFi board** to the **Arduino Uno R3** according to the diagram below:

    - **circuit diagram** *(coming soon)*

2. Connect the relay module to the **Arduino Uno R3** according to the diagram below:

    - **relay module wiring** *(coming soon)*

3. Connect the LED light bulb to the **relay module**.

4. Upload the Arduino code `(Illuine.4R.ino)` to the **Arduino Uno R3** using the **Arduino IDE**.

5. Upload the ESP8266 code `(IlluminateServer.ino)` to the **Generic ESP8266 WiFi** using the **Arduino IDE**.
    - ~~Create a new project in the Blynk app or **Web browser**, and get an authentication token.~~

    - ~~Add a button widget to the Blynk app or **web browser**, and configure it to send a value of 1 or 0 to the **Arduino Uno R3**.~~

    - ~~Paste the authentication token and WiFi credentials into the Arduino code.~~

6. Power up the **AC to DC** power supply.

7. Connect to ESP8266 board via WiFi route at home or your hotspot.

8. goto your ip-address example `http://197.172.0.8/`

9. And Enjoy it!


**<h2>Usage</h2>**
1. Open the ~~Blynk app~~ or **Web browser**.

2. Press the button widget to turn on/off the light bulb *(relay port)*.

**<h3>Compatibility Tablet</h3>**

| **Compatible** | **Incompatible** |
|----------------|------------------|
| **WebSite** *(Can make your application)* | **Blynk IoT App** *(coming soon)* |

**<h3>Plans Tablet</h3>**

| **Status** | **Task** | **Start Date** |
|------------|----------|-----------------|
| **In Progress** | **Blynk IoT App Compatible** | **2023-02-30** |
| **Waiting** | **Release WiFi.Configure extensions** | **2023-04-25** |
| **Waiting** | **Next sprint** | **2023-05-01** |


**<h3>Requirements Tablet</h3>**

| **Library Require** | **Board Require** |
|----------------|------------------|
| **WiFi** *by Arduino* | **Arduino AVR Boards** *by Arduino* |
| **Blynk** *by Volodymyr Shymanskyy* `not supported yet` | **esp8266** *by ESP8266 Community* [installation](assets/esp8266%20installation.png) |

**<h2>Acknowledgments</h2>**
This project is based on the WiFi library and ~~Blynk library~~ and the circuit diagram and relay module wiring were adapted from [**How to Use Relay With Arduino - Connecting Appliances with Arduino.**](https://www.instructables.com/How-to-use-relay-with-Arduino/)
