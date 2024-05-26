This code is written with Arduino for an ESP8266 microcontroller to read temperature and humidity data from a DHT11 sensor and publish it to an MQTT server. And control a fan to lower the temperature if it is higher than 40 degree by default.

 I am using this program to get my personal rack environment information and present with homeassistant dashboard.

 Please be aware that although the relay I'm using is rated for 5V, I've discovered that it requires connection to a 3.3V power source at the VCC pin for proper operation. Connecting it to a 5V source doesn't seem to work. In addition, set the relay to low level trigger is also required. 