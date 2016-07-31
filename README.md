# esp8266_gateway

## Reflashing
1. Install the arduino IDE [https://www.arduino.cc/en/Main/Software]
2. Install the ESP8266 addon
  1. File > Preferences
  2. Copy `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into the Additional Boards Manager URLs:
  3. Go to Tools Boards, Boards Manager
  4. Install the esp8266 addon
3. Select the Generic ESP8266 Module as your board
4. Install the WifiManager Code
  1. Sketch > Include Library > Manage Libraries
  2. Search for wifimanager and install it
5. Download the esp8266_gateway code
6. Rename NodeConfig-template.h to NodeConfig.h
7. Open esp8266_gateway.ino
8. Edit NodeConfig.h and add in your location, node ID
9. Upload the code
