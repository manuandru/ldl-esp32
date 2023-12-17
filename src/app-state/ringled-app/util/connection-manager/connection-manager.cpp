#include "connection-manager.h"
#include "freertos/FreeRTOS.h"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

ConnectionManager::ConnectionManager() {
  this->clientId = "lamp-" + String(random(0xffff), HEX);
  espClient.setCACert(root_ca);
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback([this](char *topic, byte *payload, unsigned int length) {
    this->messageHandler(topic, payload, length);
  });
}

void ConnectionManager::publishAsync() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  messageShouldBeSent = true;
  xSemaphoreGive(mutex);
}

void ConnectionManager::messageHandler(char *topic, byte *payload,
                                       unsigned int length) {
  String incomingMessage = "";
  for (int i = 0; i < length; i++)
    incomingMessage += (char)payload[i];

  if (incomingMessage.equals(this->clientId)) {
    Serial.println("Message received from self");
  } else {
    Serial.println("Message received from other");
  }
}

void ConnectionManager::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(1000);
    }
  }
}

void ConnectionManager::sendMessage() {
  client.publish(MQTT_TOPIC, String(this->clientId).c_str());
}

void ConnectionManager::loop() {
  if (!client.connected()) {
    this->reconnect();
  }
  client.loop();

  xSemaphoreTake(mutex, portMAX_DELAY);
  if (messageShouldBeSent) {
    messageShouldBeSent = false;
    xSemaphoreGive(mutex);
    this->sendMessage();
  } else {
    xSemaphoreGive(mutex);
  }
}