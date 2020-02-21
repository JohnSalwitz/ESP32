/**
 * A simple Azure IoT example for sending telemetry.
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"

static const char *clientName = "ESP_32_Test";
static WiFiClient _espClient;
static PubSubClient _client(_espClient);

static bool hasIoTHub = false;


void setup() {
  Serial.begin(115200);
  Serial.println("Starting connecting WiFi.");
  delay(10);
  
  WiFi.begin((char *)ssid, (char *)password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  _client.setServer(mqttServer, mqttPort);
    
  while (!_client.connected()) {
      if (_client.connect(clientName, mqttUser, mqttPassword)) {
          Serial.println("Connected to MQTT");
          _client.publish("esp/log", "hello from ESP32");
      } else {
          char buf[128];
          sprintf(buf, "Failed To Connect To MQTT with State: %d", _client.state());
          Serial.println(buf);
          delay(2000);
      }
  }

  hasIoTHub = true;
}

void loop() {

  if (hasIoTHub)
  {
    _client.loop();
  }
}
