/*void onMqttSubscribe(const uint16_t& packetId, const uint8_t& qos)
{
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: "); Serial.println(packetId);
  Serial.print("  qos: ");      Serial.println(qos);
}

void onMqttMessage(char* topic, char* payload, const AsyncMqttClientMessageProperties& properties, 
                   const size_t& len, const size_t& index, const size_t& total)
{
  (void) payload;
  
  if(String(topic).indexOf("doorbell") > -1){
    
  }
}

void onMqttConnect(bool sessionPresent) 
{
  mqttClient.subscribe("doorbell", 2);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttClient.connect();
  }
 

}
*/
