#include <LoRaAT.h>

LoRaAT lora(rx,tx);
String DevAddr = "00000000";
String DevEui = "0000000000000000";
String AppEui = "0000000000000000";

void setup() {
  lora.init();
  lora.setIDs(DevAddr, DevEui, AppEui);
  lora.setTimeDelay(600);

  lora.testConfig();
}

void loop() {
  Serial.println("\nSending message...");
  for(int i = 0; i < 3; i++){
    lora.sendCMsg("test");
    if(lora.waitACK()){
      Serial.println("ACK Received in " + String(i+1) + " attempts");
      i = 5;
    }else if (i == 2) {
      Serial.println("ACK Not Received in 3 attempts");
    }else {
      Serial.println("ACK Not Received, retrying.");
    }
    delay(500);
  }
  Serial.println("Delaying 8s");
  delay(8000);
}

