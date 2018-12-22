
#include <TridentTD_ESP32NVS.h>

void setup() {
  Serial.begin(115200); Serial.println();

  Serial.println("[ESP32] NVS start");
  NVS.begin();

  String  ssid        = NVS.getString("SSID");
  String  password    = NVS.getString("PASSWORD");
  char*   note        = NVS.getCharArray("NOTE");
  int16_t distance    = NVS.getInt("DISTANCE");
  float   temperature = NVS.getFloat("TEMPERATURE");

  Serial.printf("ssid        : %s\n", ssid.c_str());
  Serial.printf("password    : %s\n", password.c_str());
  Serial.printf("note        : %s\n", note );
  Serial.printf("distance    : %d cm\n", distance );
  Serial.printf("temperature : %.5f C\n", temperature );

  Serial.println();
  Serial.print("Key 'SSID'  exists?     : "); Serial.println( NVS.exists("SSID"));
  Serial.print("Key 'SSID2' exists?     : "); Serial.println( NVS.exists("SSID2"));
  Serial.print("Key 'DISTANCE'  exists? : "); Serial.println( NVS.exists("DISTANCE"));
  Serial.print("Key 'DISTANCE2' exists? : "); Serial.println( NVS.exists("DISTANCE2"));

  if(!NVS.exists("BRIGHTNESS")){
    NVS.setInt("BRIGHTNESS", (uint8_t) 128 );
  }

  uint8_t brightness =  (uint8_t) NVS.getInt("BRIGHTNESS");
  Serial.printf("brightness  : %d\n", brightness );

  NVS.erase("BRIGHTNESS");
}

void loop() {
  delay(1);
}


