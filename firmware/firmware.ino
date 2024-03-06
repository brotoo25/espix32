#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>

const char* ssid = "Home-Lab";
const char* password = "&^dysz\3&Q6V9kY~";
const char* mqtt_server = "jefcfa3e.ala.asia-southeast1.emqxsl.com";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  M5.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(mqtt_server, 8883);
  client.setCallback(callback);
  fetchAndDisplayImage();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void fetchAndDisplayImage() {
  HTTPClient http;
  http.begin("https://hook.us1.make.com/saj9d8pigyktdx5wu883vrdey6gbl58j");
  int httpCode = http.GET();
  if (httpCode == 200) {
    String newImageUrl = http.getString();
    http.end();
    displayImageFromUrl(newImageUrl);
  } else {
    http.end();
  }
}

void displayImageFromUrl(String url) {
  // Placeholder for image download and display
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("M5StackClient")) {
      client.subscribe("your/topic");
    }
    delay(5000);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  displayCheckIcon();
  digitalWrite(LEDPin, HIGH);
  delay(5000);
  fetchAndDisplayImage();
}

void displayCheckIcon() {
  // Placeholder for check icon display
}

int LEDPin = 2; // Change to your LED pin
