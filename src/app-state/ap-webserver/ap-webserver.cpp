#include "ap-webserver.h"
#include <Arduino.h>
#include <Preferences.h>
#include <WebServer.h>
#include <WiFi.h>

void handleClientTask(void *parameter) {
  WebServer *server = (WebServer *)parameter;
  while (1) {
    server->handleClient();
    delay(1);
  }
}

APWebServer::APWebServer(RingLed *ringLed) {

  this->ringLed = ringLed;
  this->ringLed->setCredentialsMissingColor();

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.begin();
  server.on("/", HTTP_GET, std::bind(&APWebServer::handleRoot, this));
  server.on("/setup", HTTP_POST,
            std::bind(&APWebServer::handleCredentialsSetup, this));
  server.onNotFound(std::bind(&APWebServer::handleNotFound, this));

  Serial.println("Server started");

  xTaskCreate(handleClientTask, "handleClientTask", 10000, &server, 1, NULL);
}

void APWebServer::handleRoot() {
  this->ringLed->setSiteConnectedColor();
  server.send(200, "text/html", html);
}

void APWebServer::handleCredentialsSetup() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  Serial.println("ssid: " + ssid);
  Serial.println("password: " + password);

  Preferences preferences;
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();

  server.send(200, "text/html", okHtml);
  delay(1000);
  ESP.restart();
}

void APWebServer::handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
