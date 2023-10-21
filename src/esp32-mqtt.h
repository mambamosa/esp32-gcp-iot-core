#include "ciotc_config.h"

#include <Client.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h>

#include <WiFiManager.h>
#include <MQTT.h>

#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Update.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "time.h"
#include "esp_system.h"

// Initialize WiFi and MQTT
WiFiManager wm;
WebServer server(80);

WiFiClient client;
WiFiClientSecure *netClient;

CloudIoTCoreDevice *device;
CloudIoTCoreMqtt *mqtt;
MQTTClient *mqttClient;

void setupWifi(){
    unsigned long connectMillis = 0;

    String version = String("<p>Current Version - v") + "1.0.0" + String("</p>");
    WiFiManagerParameter versionText(version.c_str());
    Serial.println(version);
    wm.addParameter(&versionText);
    // Define a time period (seconds) in which client should establish a connection with the target host (24hrs = 86400s)
    wm.setConnectTimeout(10);  
    WiFi.mode(WIFI_STA);
    if (!wm.autoConnect("mambamosa")) {
        // wm.resetSettings();
        connectnetwork = false;
        Serial.println("[INTERNET] Failed to connect. Proceed to web portal to configure wifi.");
    }
    else {
        connectnetwork = true;
        Serial.println("[INTERNET] Connected!");
    }
    configTime(28800, 0, ntp_primary, ntp_secondary);
    Serial.println("[NTP] Waiting on time sync...");
    if (WiFi.status() != WL_CONNECTED) {
      return;
    }
    else {
        while (time(nullptr) < 1510644967) {
            wm.process();
            delay(10);
        }
    }
    Serial.print("[INTERNET] IP address: "); Serial.println(WiFi.localIP());
}

String getDefaultSensor(){
  return "Wifi: " + String(WiFi.RSSI()) + "db";
}

String getValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// MQTT callback functions for commands
void messageReceived(String &topic, String &message) {
    Serial.println("[MQTT] Incomming command: " + topic + " - " + message);
    int index = message.indexOf(':');
    if (message.startsWith("hello")) {
        Serial.println("Hello World!");
    }
    if (message.startsWith("restart")) {
        esp_restart();
    }
}

bool publishTelemetry(String data){
    return mqtt->publishTelemetry(data);
}

bool publishTelemetry(const char *data, int length){
    return mqtt->publishTelemetry(data, length);
}

bool publishTelemetry(String subfolder, String data){
    return mqtt->publishTelemetry(subfolder, data);
}

bool publishTelemetry(String subfolder, const char *data, int length){
    return mqtt->publishTelemetry(subfolder, data, length);
}

void publishState(String data){
    mqttClient->publish(device->getStateTopic(), data);
}

String getJwt(){
    iat = time(nullptr);
    Serial.println("[MQTT] Refreshing JWT...");
    jwt = device->createJWT(iat, jwt_exp_secs);
    return jwt;
}

void mqttConnect(){
    Serial.println("[MQTT] Connecting...");
    while(!mqttClient->connect(device->getClientId().c_str(), "unused", getJwt().c_str(), false)){
        Serial.print("[MQTT-error] Last error: ");
        Serial.println(mqttClient->lastError());
        Serial.print("[MQTT-error] Return code: ");
        Serial.println(mqttClient->returnCode());
        delay(1000);
    }
    Serial.println("[MQTT] Connected.");
    mqttClient -> subscribe(device->getConfigTopic());
    mqttClient -> subscribe(device->getCommandsTopic());
    publishState("Connected");
}

void startMQTT(){
    mqttClient -> begin("mqtt.googleapis.com", 8883, *netClient);
    mqttClient -> onMessage(messageReceived);
}

void setupCloudIoT(){
    device = new CloudIoTCoreDevice(
        project_id, location, registry_id, device_id, private_key_str
    );
    netClient = new WiFiClientSecure();
    ((WiFiClientSecure*)netClient) -> setCACert(root_cert);
    mqttClient = new MQTTClient(512);
    // keepAlive, cleanSession, timeout
    mqttClient -> setOptions(300, true, 1000);
    mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
    mqtt -> setUseLts(true);
    mqtt -> startMQTT();
}