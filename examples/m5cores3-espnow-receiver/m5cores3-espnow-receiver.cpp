/**************************************************
 * ESP32Cam video ESPNow Receiver
 * by @hpsaturn Copyright (C) 2024
 * This file is part ESP32S3 camera tests project:
 * https://github.com/hpsaturn/esp32s3-cam
**************************************************/

#include <M5CoreS3.h>
#include "ESPNowCam.h"
#include "Utils.h"

ESPNowCam radio;

// frame buffer
uint8_t *fb; 
// display globals
int32_t dw, dh;

void onDataReady(uint32_t lenght) {
  CoreS3.Display.drawJpg(fb, lenght , 0, 0, dw, dh);
  printFPS("M5CoreS3: ");
}

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();
  CoreS3.begin(cfg);
  CoreS3.Display.setTextColor(GREEN);
  CoreS3.Display.setTextDatum(middle_center);
  CoreS3.Display.setFont(&fonts::Orbitron_Light_24);
  CoreS3.Display.setTextSize(1);

  dw = CoreS3.Display.width();
  dh = CoreS3.Display.height();

  if(psramFound()){
    size_t psram_size = esp_spiram_get_size() / 1048576;
    Serial.printf("PSRAM size: %dMb\r\n", psram_size);
  }

  // BE CAREFUL WITH IT, IF JPG LEVEL CHANGES, INCREASE IT
  fb = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;

  radio.setRecvBuffer(fb);
  radio.setRecvCallback(onDataReady);

  if (radio.init()) {
    M5.Display.drawString("ESPNow Init Success", dw / 2, dh / 2);
  }
  delay(1000);
}

void loop() {
}
