
#include <PubSubClient.h>

const char* mqtt_server = "192.168.1.184";

WiFiClient espClient;
PubSubClient client(espClient);

const char* topicToPublish = "/test/message/water";

long lastMsg = 0;
String msg;
int value = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
