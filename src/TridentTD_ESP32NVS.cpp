// TridentTD_TridentTD_ESP32NVS.cpp
//
// Copyright (c) 2016-2018 TridentTD
//
// History : 
// V.1.0  @ 21/11/2560 Buddism Era ( 2017 )   by TridentTD
//        First release
// V.1.1  @ 22/12/2561 Buddism Era ( 2018 )   by TridentTD
//        Support isExist() for checking key is exist on NVS or not?
// V.1.2  @ 10/06/2563 Buddism Era ( 2020 )   by TridentTD
//        Fix bug ... malloc and free heap mem
// V.1.3  @ 27/11/2563 Buddism Era ( 2020 )   by TridentTD
//        add APIs 
//         - getObject(String key, void* blob, size_t length);  for loading struct data from NVS
//         - setBool(...) & getBool(...)
//

#include "TridentTD_ESP32NVS.h"

TridentTD_ESP32NVS::TridentTD_ESP32NVS(){
}


bool TridentTD_ESP32NVS::begin(){
  _err = nvs_flash_init();
  if (_err == ESP_ERR_NVS_NO_FREE_PAGES) {
    const esp_partition_t* nvs_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
    _err = (esp_partition_erase_range(nvs_partition, 0, nvs_partition->size));
  }
  _err = nvs_open("storage", NVS_READWRITE, &_nvs_handle);

  if(_err != ESP_OK) return false;
  return true;  
}

void TridentTD_ESP32NVS::close(){
   nvs_close(_nvs_handle);
}

bool TridentTD_ESP32NVS::eraseAll(){
  _err = nvs_erase_all(_nvs_handle);
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::erase(String key){
  _err =  nvs_erase_key(_nvs_handle, key.c_str());
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::commit(){
  _err = nvs_commit(_nvs_handle);
  if(_err != ESP_OK) return false;
  return true;
}




bool TridentTD_ESP32NVS::setInt(String key, uint8_t value){
  _err = nvs_set_u8(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool TridentTD_ESP32NVS::setInt(String key, int16_t value){
  _err = nvs_set_i16(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::setInt(String key, uint16_t value){
  _err = nvs_set_u16(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool TridentTD_ESP32NVS::setInt(String key, int32_t value){
  _err = nvs_set_i32(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::setInt(String key, uint32_t value){
  _err = nvs_set_u32(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}
bool TridentTD_ESP32NVS::setInt(String key, int64_t value){
  _err = nvs_set_i64(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::setInt(String key, uint64_t value){
  _err = nvs_set_u64(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit();
}

bool TridentTD_ESP32NVS::setCharArray(String key, const char* value){
  _err = nvs_set_str(_nvs_handle, (char*)key.c_str(), value);
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool TridentTD_ESP32NVS::setString(String key, String value){
  _err = nvs_set_str(_nvs_handle, (char*)key.c_str(), (char*)value.c_str());
  if(_err != ESP_OK) return false;
  return commit(); 
}

bool TridentTD_ESP32NVS::setObject(String key, void* value, size_t length){
  _err = nvs_set_blob(_nvs_handle, (char*)key.c_str(), value, length);
  if(_err != ESP_OK) return false;
  return commit();
}


int64_t TridentTD_ESP32NVS::getInt(String key){
  uint8_t   v_u8;
  int16_t   v_i16;
  uint16_t  v_u16;
  int32_t   v_i32;
  uint32_t  v_u32;
  int64_t   v_i64;
  uint64_t  v_u64;

  _err = nvs_get_u8(_nvs_handle, (char*)key.c_str(), &v_u8);
  if(_err == ESP_OK) return (int64_t) v_u8;

  _err = nvs_get_i16(_nvs_handle, (char*)key.c_str(), &v_i16);
  if(_err == ESP_OK) return (int64_t) v_i16;

  _err = nvs_get_u16(_nvs_handle, (char*)key.c_str(), &v_u16);
  if(_err == ESP_OK) return (int64_t) v_u16;

  _err = nvs_get_i32(_nvs_handle, (char*)key.c_str(), &v_i32);
  if(_err == ESP_OK) return (int64_t) v_i32;

  _err = nvs_get_u32(_nvs_handle, (char*)key.c_str(), &v_u32);
  if(_err == ESP_OK) return (int64_t) v_u32;

  _err = nvs_get_i64(_nvs_handle, (char*)key.c_str(), &v_i64);
  if(_err == ESP_OK) return (int64_t) v_i64;

  _err = nvs_get_u64(_nvs_handle, (char*)key.c_str(), &v_u64);
  if(_err == ESP_OK) return (int64_t) v_u64;

  return 0;
}

String TridentTD_ESP32NVS::getString(String key){
  size_t required_size;
  nvs_get_str(_nvs_handle, key.c_str(), NULL, &required_size);
  char* value = (char*) malloc(required_size);
  nvs_get_str(_nvs_handle, key.c_str(), value, &required_size);
  String buf = String(value);
  if(value != NULL && required_size) free(value);
  return buf;
}

char* TridentTD_ESP32NVS::getCharArray(String key, char* rev_data) {
  if( rev_data != NULL) {
    free(rev_data); rev_data = NULL;
  }
  size_t required_size;
  nvs_get_str(_nvs_handle, key.c_str(), NULL, &required_size);

  rev_data = (char*) malloc(required_size);
  nvs_get_str(_nvs_handle, key.c_str(), rev_data, &required_size);
  return rev_data;
}

void* TridentTD_ESP32NVS::getObject(String key, void* blob){
  if( blob != NULL) {
    free(blob); blob = NULL;
  }
  size_t required_size;
  nvs_get_blob(_nvs_handle, key.c_str(), NULL, &required_size);
  blob = (void*) malloc(required_size);
  nvs_get_blob(_nvs_handle, key.c_str(), blob, &required_size);
  return blob;
}

bool TridentTD_ESP32NVS::getObject(String key, void* blob, size_t length){
  size_t required_size;
  nvs_get_blob(_nvs_handle, key.c_str(), NULL, &required_size);
  if(required_size != length) return false;
  
  return ( ESP_OK == nvs_get_blob(_nvs_handle, key.c_str(), blob, &required_size) );
}

bool TridentTD_ESP32NVS::setFloat(String key, float value){
  return setObject( key, &value, sizeof(float));
}

float TridentTD_ESP32NVS::getFloat(String key){
  float *pFloat=NULL;
  pFloat = (float*) getObject(key, pFloat);
  float buf = *pFloat;
  if(pFloat != NULL) free(pFloat);
  return buf;
}

bool TridentTD_ESP32NVS::exists(String key){
  uint8_t   v_u8;
  int16_t   v_i16;
  uint16_t  v_u16;
  int32_t   v_i32;
  uint32_t  v_u32;
  int64_t   v_i64;
  uint64_t  v_u64;

  _err = nvs_get_u8(_nvs_handle, (char*)key.c_str(), &v_u8);
  if(_err == ESP_OK) return true;

  _err = nvs_get_i16(_nvs_handle, (char*)key.c_str(), &v_i16);
  if(_err == ESP_OK) return true;

  _err = nvs_get_u16(_nvs_handle, (char*)key.c_str(), &v_u16);
  if(_err == ESP_OK) return true;

  _err = nvs_get_i32(_nvs_handle, (char*)key.c_str(), &v_i32);
  if(_err == ESP_OK) return true;

  _err = nvs_get_u32(_nvs_handle, (char*)key.c_str(), &v_u32);
  if(_err == ESP_OK) return true;

  _err = nvs_get_i64(_nvs_handle, (char*)key.c_str(), &v_i64);
  if(_err == ESP_OK) return true;

  _err = nvs_get_u64(_nvs_handle, (char*)key.c_str(), &v_u64);
  if(_err == ESP_OK) return true;

  size_t required_size;
  _err = nvs_get_str(_nvs_handle, key.c_str(), NULL, &required_size);
  if(_err == ESP_OK) return true;

  _err = nvs_get_blob(_nvs_handle, key.c_str(), NULL, &required_size);
  if(_err == ESP_OK) return true;

  return false;
}


// bool TridentTD_ESP32NVS::setDouble(String key, double value){
//   return setObject( key, &value, sizeof(double));
// }

// double TridentTD_ESP32NVS::getDouble(String key){
//   double *pDouble = (double*) getObject(key);
//   return *pDouble;
// }

nvs_handle TridentTD_ESP32NVS::get_nvs_handle(){
  return _nvs_handle;
}

#ifdef VERSION_EXTRA
typedef struct nvs_entry
{
  uint8_t  Ns ;         // Namespace ID
  uint8_t  Type ;       // Type of value
  uint8_t  Span ;       // Number of entries used for this item
  uint8_t  Rvs ;        // Reserved, should be 0xFF
  uint32_t CRC ;        // CRC
  char     Key[16] ;    // Key in Ascii
  uint64_t Data ;       // Data in entry 
} nvs_entry_t;

typedef struct nvs_page                             // For nvs entries
{                                                   // 1 page is 4096 bytes
  uint32_t  State ;
  uint32_t  Seqnr ;
  
  uint32_t  Unused[5] ;
  uint32_t  CRC ;
  uint8_t   Bitmap[32] ;
  nvs_entry Entry[126] ;
} nvs_page_t;

static uint8_t FindNsID ( const esp_partition_t* nvs, const char* ns ) {
  uint32_t    offset = 0 ;                      // Offset in nvs partition
  uint8_t     res = 0xFF ;                      // Function result
  nvs_page_t  nvs_page;

  while ( offset < nvs->size ){
    if (  ESP_OK != esp_partition_read ( nvs, offset, &nvs_page, sizeof(nvs_page) ) ) {
      Serial.println( "Error reading NVS!" ) ;
      break ;
    }

    uint8_t i = 0 ;
    while ( i < 126 ) {
      uint8_t  bm = ( nvs_page.Bitmap[i/4] >> ( ( i % 4 ) * 2 ) ) & 0x03 ;  // Get bitmap for this entry
      if ( ( bm == 2 ) && ( nvs_page.Entry[i].Ns == 0 ) && ( strcmp ( ns, nvs_page.Entry[i].Key ) == 0 ) ) {
        uint8_t res = nvs_page.Entry[i].Data & 0xFF ;                      // Return the ID
        offset = nvs->size ;                                  // Stop outer loop as well
        break ;
      } else {
        if ( bm == 2 ) {
          i += nvs_page.Entry[i].Span ;                             // Next entry
        } else {
          i++ ;
        }
      }
    }
    offset += sizeof(nvs_page) ;                              // Prepare to read next page in nvs
  }
  return res ;
}

typedef enum {NVS_UINT8_T=1,  NVS_UINT16_T=2, NVS_UINT32_T=4, NVS_UINT64_T=8,
              NVS_INT8_T=17/*?*/, NVS_INT16_T=18, NVS_INT32_T=20, NVS_INT64_T=24, 
              NVS_STRING=33, NVS_BLOB=65 } NVS_TYPE_t;

static String NVS_Datatype(uint8_t type){
  String type_str;
  switch((NVS_TYPE_t)type){
    case NVS_UINT8_T:   type_str = "uint8_t";   break;
    case NVS_UINT16_T:  type_str = "uint16_t";  break;
    case NVS_UINT32_T:  type_str = "uint32_t";  break;
    case NVS_UINT64_T:  type_str = "uint64_t";  break;
    case NVS_INT8_T:    type_str = "int8_t";    break;
    case NVS_INT16_T:   type_str = "int16_t";   break;
    case NVS_INT32_T:   type_str = "int32_t";   break;
    case NVS_INT64_T:   type_str = "int64_t";   break;
    case NVS_STRING:    type_str = "String";    break;
    case NVS_BLOB:      type_str = "blob";      break;
    default:            type_str = String(type);break;
  }
  return type_str;
}

static String getIntString(uint64_t val,uint8_t type){
  String int_str;

  switch((NVS_TYPE_t)type){
    case NVS_UINT8_T:   int_str = String((uint8_t)val);   break;
    case NVS_UINT16_T:  int_str = String((uint16_t)val);  break;
    case NVS_UINT32_T:  int_str = String((uint32_t)val);  break;
    case NVS_UINT64_T:  int_str = ""; /*String((uint64_t)val);*/  break;
    case NVS_INT8_T:    int_str = String((int8_t)val);    break;
    case NVS_INT16_T:   int_str = String((int16_t)val);   break;
    case NVS_INT32_T:   int_str = String((int32_t)val);   break;
    case NVS_INT64_T:   int_str = ""; /*String((int64_t)val);*/   break;
    case NVS_STRING:    int_str = "";    break;
    case NVS_BLOB:      int_str = "";    break;
    default:            int_str = "";    break;
  }
  return int_str;
}


void TridentTD_ESP32NVS::listKeys(){
  esp_partition_iterator_t  partition_it = esp_partition_find ( ESP_PARTITION_TYPE_DATA,  ESP_PARTITION_SUBTYPE_ANY, "nvs" ) ;
  if(partition_it) {
    const esp_partition_t* nvs = esp_partition_get(partition_it);
    uint8_t namespace_ID = FindNsID ( nvs, "ESP32Radio" ) ;
    nvs_page_t nvs_page;
    // Serial.println(nvs->size);
    int s=0;
    while( s < nvs->size ){
      if( ESP_OK == esp_partition_read( nvs, s, &nvs_page, sizeof(nvs_page_t))){
        int i = 0;
        while (i < 126) {
          byte bm = ( nvs_page.Bitmap[i/4] >> ((i%4)*2)) & 0x03;
          if(bm == 2) {
            if( namespace_ID == 255  || nvs_page.Entry[i].Ns == namespace_ID ) {
              Serial.printf( "[%03d][%10s]   %-16s   %s\n", 
                i, NVS_Datatype(nvs_page.Entry[i].Type).c_str(), nvs_page.Entry[i].Key, 
                getIntString(nvs_page.Entry[i].Data, nvs_page.Entry[i].Type).c_str() );
            }
            i += nvs_page.Entry[i].Span;
          }else{
            i++;
          }
        }
        s += sizeof(nvs_page_t);
      }
    }
  } else{
    Serial.println("Partition NVS not found");
  }
}
#endif


TridentTD_ESP32NVS NVS;

