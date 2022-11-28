#include "sound.h"
#include "XT_DAC_Audio.h"
#include <esp_now.h>
#include <WiFi.h>


bool shouldPlay;
bool ring;

XT_Wav_Class Sound(sound);
XT_DAC_Audio_Class DacAudio(25, 0);



void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  ring= true;
}



void setup() {
  Serial.begin(115200);


  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_register_recv_cb(OnDataRecv);
 

}

void loop() {
  // play audio sound when data recievd
  if (ring) {
    DacAudio.FillBuffer();
    if (Sound.Playing == false){
      DacAudio.Play(&Sound);
      shouldPlay = true; // prevent clip from stopping before its played
    }
      
  }

  // stop playing when full clip is played
  if (Sound.TimeLeft <= 100 && shouldPlay) {
        Serial.println("stopping");
    ring = false;
    shouldPlay = false;
  }

  
}
