#include <esp_now.h>
#include <WiFi.h>
#include <AsyncMqtt_Generic.h>
#define INTERRUPT_PIN 15
uint8_t broadcastMacAddress[] = {0XC0, 0x49, 0xEF, 0XE4, 0x4B, 0x00};



#define MQTT_HOST  IPAddress(132, 145, 71, 107)
#define MQTT_PORT  1883
#define WIFI_SSID  "MSKCTYWifi"
#define WIFI_PASSWORD "TheBestIWMSKCTY"

AsyncMqttClient mqttClient;

#include "mqtt.h"

 bool ring_bell;

 
