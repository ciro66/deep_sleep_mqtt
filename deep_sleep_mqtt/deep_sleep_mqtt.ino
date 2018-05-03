#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

WiFiClient wclient;
PubSubClient MQTTclient(wclient);

const char* ssid ="*****************";
const char* password = "*****************";
char msg[50];

void setup() {
  Serial.begin(115200);

  setup_wifi();
  MQTTclient.setServer("***.***.***.***", 1883);
  MQTTclient.connect("ESP8266Client");

  Serial.println("MQTTclient connected");
}

void loop() {
  int i = random(100);
  sprintf(msg, "%d", i);
  Serial.println(msg);
  MQTTclient.publish("temp", msg);
  delay(2000);
  Serial.println("Ora vado in deep sleep per 20 secondi");
  ESP.deepSleep(20e6); // 20e6 sono 20 secondi
  // delay(2000);
}
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

