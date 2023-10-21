# (deprecated) esp32-gcp-iot-core
[![ESP32](https://img.shields.io/badge/ESP-32-000000.svg?longCache=true&style=flat&colorA=CC101F)](https://www.espressif.com/en/products/socs/esp32)
![ARDUINO](https://img.shields.io/badge/-Arduino-blue)
![PLATFORMIO](https://img.shields.io/badge/-PlatformIO-orange)
![GCP-IOT-CORE](https://img.shields.io/badge/GCP-IOT%20Core-4285F4)

## NOTICE
> **Google Cloud IoT Core has been officially retired on August 16, 2023.** No device can be connected to Google Cloud IoT Core MQTT as well as HTTP bridges. All connections are going to shut down beyond that date.

## CONTENTS
- [Hardware Compatibility](#hardware-compatibility)
- [Libraries](#libraries)
- [High Level Architecture Diagram](#high-level-architecture-diagram)

---
### Hardware Compatibility
The project can show how you can use this firmware with various Arduino compatible hardware:
- ESP32 Dev Kit V1 Development Board
- ESP8266 Development Board

### Libraries
- [WiFiManager](https://github.com/tzapu/WiFiManager)
- [google-cloud-iot-arduino](https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino)
- [arduino-mqtt](https://github.com/256dpi/arduino-mqtt)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

### High Level Architecture

![image](esp32-gcp-iot-core-diagram.png)
> This project demonstrates the workflow from IoT devices to Device Registry only. Data Ingestion, Storage, and Analysis workflows are developed and deployed separately.