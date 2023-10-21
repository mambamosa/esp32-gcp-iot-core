#include <Arduino.h>
#include "esp32-mqtt.h"

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    
    setupWifi();

    setupCloudIoT();
}

unsigned long publishMillis = 0;
void loop() {
    mqtt->loop();
    delay(10);      // Fixes some issues with WiFi stability

    if (!mqttClient -> connected()) {
        mqtt->mqttConnect();
    }
    
    wm.process();

    if (millis() - publishMillis >= 10000) {
        publishMillis = millis();
        publishTelemetry(getDefaultSensor());
    }
}