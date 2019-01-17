#include <LoRaAT.h>

LoRaAT lora(rx,tx);
String DevAddr = "00000000";
String DevEui = "0000000000000000";
String AppEui = "0000000000000000";
  
void setup() {
  lora.init();
  lora.setIDs(DevAddr, DevEui, AppEui);
  lora.setKeys(NwkSkey, AppSkey);
  //lora.setDevAddr(DevAddr);
  //lora.setDevEui(DevEui);
  //lora.setAppEui(AppEui);
  lora.setTimeDelay(600);
  
  lora.testConfig();
}

void loop() {
  lora.loop();
}

