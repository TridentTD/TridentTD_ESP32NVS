TridentTD_ESP32NVS Library
==========================

**TridentTD_ESP32NVS** เป็นไลบรารี่ สำหรับ ESP32 บน Arduino Platform  
สำหรับการจัดเก็บค่าของตัวแปรไว้บน พื้นที่ NVS (Non-volatile storage)  บน ESP32  
ในรูปแบบชอง key, value  
แม้จะมีการ Reboot ตัวอุปกรณ์ ESP32 ก็ยังจดจำค่าไว้ได้อยู่  
  
NVS จะคล้ายๆ กับการจัดเก็บแบบ EEPROM แต่ไม่จำเป็นต้องกำหนด Address  
และมีความสะดวกต่อการใช้งานกว่าการจัดเก็บแบบ EEPROM  
เพราะจัดเก็บในรูปแบบ key & value โดยตรงเลย  
  
  
## วิธีใช้ (Usage)

ให้ ทำการ include ไลบรารี่ ด้วย  

```
#include <TridentTD_ESP32NVS.h>
```
  
แล้วเริ่มต้นการใช้งาน NVS ทุกครั้ง ด้วยคำสั่ง  
  
```
NVS.begin();
```
  
  
  
### การจัดเก็บแบบ Interger, Float, String, Char Array

ในการจัดเก็บข้อมูลตัวแปร สามารถจัดเก็บลงบน NVS ได้ตามประเภทตัวแปร ดังนี้  
  
```
NVS.setInt("myInt", 23);             // จัดเก็บค่าจำนวนเต็ม 23 ลงที่ key ชื่อ "myInt" บน NVS
NVS.setFloat("myFloat",94.534 );     // จัดเก็บค่าจำนวนจริง 94.534 ลงที่ key ชื่อ "myFloat" บน NVS

String data1 = "Hello String";
NVS.setString("myString", data );    // จัดเก็บค่าข้อความ data ลงที่ key ชื่อ "myString" บน NVS

const char* data2 = "Hello Char Array";
NVS.setCharArray("myChArr", data2);  // จัดเก็บค่าข้อความ data2 ลงที่ key ชื่อ "myCharArray" บน NVS
```
  
ในการเรียกข้อมูลจาก NVS สามารถเรียกใช้ได้โดยง่าย ดังนี้  
  
```
int i  = NVS.getInt("myInt");      // อ่านค่า ของ key "myInt" บน NVS มาเก็บที่ตัวแปร i
float f = NVS.getFloat("myFloat"); // อ่านค่า ของ key "myFloat" บน NVS มาเก็บที่ตัวแปร f
String str = NVS.getString("myString");  // อ่านค่า ของ key "myString" บน NVS มาเก็บที่ตัวแปร str
char* c_str= NVS.getCharArray("myChArr"); // อ่านค่า ของ key "myChArr" บน NVS มาเก็บที่ตัวแปร c_str
```
  
  
### การจัดเก็บแบบ Object
  
การจัดเก็บตัวแปรนอกอื่นๆ นอกเหนือ จาก ประเภทตัวแปรพื้นฐานข้างต้น  
เช่น การจัดเก็บ array ของ integer , การจัดเก็บข้อมูล struct เป็นต้น  
จะสามารถจัดเก็บ โดยใช้คำสั่งแบบ object ดังตัวอย่าง  
  
```
uint8_t mac[6] = {0xDF, 0xEE, 0x10, 0x49, 0xA1, 0x42};
NVS.setObject( "MAC", &mac, sizeof(mac) );  // จัดเก็บค่า mac[6] ลงที่ key ชื่อ "MAC" บน NVS
```
  
วิธีการเรียกข้อมูลแบบ object ที่บันทึกบน NVS  
  
```
uint8_t* mymac;
mymac = (uint8_t*) NVS.getObject( "MAC");   // อ่านค่า key ชื่อ "MAC" บน NVS มาเก็บไว้ที่ตัวแปร mymac

Serial.printf("mac : %02X:%02X:%02X:%02X:%02X:%02X\n", 
               mymac[0],mymac[1],mymac[2],mymac[3],mymac[4],mymac[5]);
               
```
  
  
  
Version
----- 
1.0  TridentTD  
21 November 2560 Buddism Era ( 2017 )  
  
1.1 TridentTD : add exists() function  
22 December 2561 Buddism Era ( 2018 )  
