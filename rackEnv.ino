#include <SimpleDHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int pinDHT11 = 2; // GPIO2 of ESP8266
const char* ssid = "qi";//wifi ssid
const char* password = "xxxxxxx";//wifi password
const char* mqtt_server = "192.168.50.102";//mqtt server address

//const String macAddress = WiFi.macAddress();
//const char* clientID = macAddress.c_str();    //MAC address
const char* clientID = "rackenv_dht11";

WiFiClient espClient;
PubSubClient client(espClient);
SimpleDHT11 dht11(pinDHT11);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  WiFi.begin(ssid, password);    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi connected");
}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.println("Message arrived ["); Serial.print(topic);   Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.println((char)payload[i]);
  }  
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("reconnecting mqtt...");
    delay(1000);
    if (client.connect(clientID,"admin","mengqi2")) {               //connected
      Serial.print("MQTT connected!");                
    } else {
      delay(5000);                                
    }
  }
}
void loop() {
  Serial.println("start loop");
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.println("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
  } else {
      client.publish("rack/temperature", String(temperature).c_str());  //publish temperature
      client.publish("rack/humidity", String(humidity).c_str());        //publish humidity
      delay(3600000);
  }
}