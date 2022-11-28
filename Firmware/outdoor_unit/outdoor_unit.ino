#include "definitions.h"

 
 String message = "ring";

esp_now_peer_info_t peerInfo;



// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
 ring_bell = status == ESP_NOW_SEND_SUCCESS ?  false : true;
 Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void IRAM_ATTR ringInterrupt(){
 ring_bell = true;
 
}


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  
  attachInterrupt(INTERRUPT_PIN, ringInterrupt, FALLING);
  /*mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED);

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
   mqttClient.connect();
*/
}

void loop() {
  
  if(ring_bell){
    
   // send data to indoor unit
   esp_err_t result = esp_now_send(broadcastMacAddress, (uint8_t *) &message, sizeof(message));
  if (result == ESP_OK) {
        ring_bell = false;
      }
  } 
}
