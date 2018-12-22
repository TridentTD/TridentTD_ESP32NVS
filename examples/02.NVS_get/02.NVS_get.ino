
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
  Serial.print("Key 'SSID'  is exist?     : "); Serial.println( NVS.isExist("SSID"));
  Serial.print("Key 'SSID2' is exist?     : "); Serial.println( NVS.isExist("SSID2"));
  Serial.print("Key 'DISTANCE'  is exist? : "); Serial.println( NVS.isExist("DISTANCE"));
  Serial.print("Key 'DISTANCE2' is exist? : "); Serial.println( NVS.isExist("DISTANCE2"));
  
}

void loop() {
  delay(1);
}
