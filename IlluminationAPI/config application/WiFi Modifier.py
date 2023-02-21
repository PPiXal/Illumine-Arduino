import signal
import serial
import time

import os
import configparser

def cls() -> None:
    """Clears the console screen."""
    os.system('cls' if os.name == 'nt' else 'clear')
cls()


def HomeScreen(returnsback: bool = False) -> None:
    if returnsback:
        print("\n\nHave something errors or incorrectly, Please try again!")
        input("Press Enter to Execute again...")
        cls()
    else:
        input("Press Enter to continue executing")
    Execute()

def Execute() -> None:

    if not os.path.exists("Settings.ini"):
        with open("Settings.ini", 'w+') as f:
            f.write("[Ports Connection]\nesp8266_port=COM5\n\n[WiFi Modifier]\nssid=\npassword=")
        print("Files Settings.ini has been generate, please check your folder!")
        HomeScreen(False)

    config = configparser.ConfigParser()
    config.read('Settings.ini')

    try:
        ssid=config.get("WiFi Modifier", "ssid")
        password=config.get("WiFi Modifier", "password")
        esp8266Port=config.get("Ports Connection", "esp8266_port").upper()
    except:
        print(f"Error to fetch data from Setting.ini")
        HomeScreen(True)

    # Replace ? character with - in SSID and Password
    delimiter = '?'
    ssid = ssid.replace(delimiter, '-')
    password = password.replace(delimiter, '-')

    # state loading animation
    states = ["-", "/", "|", "\\"]
    # Interrupted Boolean
    interrupted = False


    if not (esp8266Port.startswith('COM') and esp8266Port[-1].isdigit()):
        print("'esp8266_port' field in 'Ports Connection' section is invalid syntax port.")
        HomeScreen(True)
    elif not ssid:
        print("Error: 'ssid' field in 'WiFi Modifier' section cannot be empty.")
        HomeScreen(True)        

    def signal_handler(signal: signal.Signals, frame: any) -> bool:
        print('Interrupted')
        global interrupted
        interrupted = True

    def UIP_Changer(SSID: str, Password: str) -> bool:
        if interrupted: return False
        state_index = 0
        sps = len(SSID+Password)
        while sps > state_index:
            if sps // 2 > state_index:
                address = SSID
                cls()
            else:
                address = Password
                cls()

            print(f"Compiling data {states[state_index % len(states)]} ({(address).encode('utf-8').hex()})", end="\r")
            state_index += 1
            time.sleep(0.2)
        wifi_uip_changed = f"{SSID}{delimiter}{Password}"
        cls()
        print("Compile data successfully!\n")
        print(f'Sending data to esp8266', end="\r");time.sleep(sps/100)
        try:
            serial.Serial(port=esp8266Port, baudrate=115200, timeout=.1).write(wifi_uip_changed.encode('utf-8'))
        except serial.SerialException as SerialExcept:
            print(f"{SerialExcept}")
            HomeScreen(True)

        print('Sent data to esp8266 successfully')
        return True

    signal.signal(signal.SIGINT, signal_handler)

    if UIP_Changer(SSID=ssid, Password=password):
        print("  Resetting the ESP8266 WiFi board is necessary for changes to take effect.")
        HomeScreen(False)
    else:
        print(f"Connection between computer and ESP8266 has been interrupted. Please try again later.")
        HomeScreen(True)


Execute()