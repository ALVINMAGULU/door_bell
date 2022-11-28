#include <esp_now.h>
#include <WiFi.h>
#define INTERRUPT_PIN 15

uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xE4, 0x4B, 0x00};
 
 String message = "ring";
 bool ring_bell;
 
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
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  
  attachInterrupt(INTERRUPT_PIN, ringInterrupt, FALLING);

}

void loop() {
  
  //send message 
  if(ring_bell){
    esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
    } 
}
