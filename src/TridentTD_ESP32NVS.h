// TridentTD_TridentTD_ESP32NVS.h
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
// V.1.4  @ 18/08/2566 Buddism Era (2023)     by TridentTD
//         - cast bool to uint8_t in setBool(..)
//

#ifndef __TRIDENTTD_ESP32NVS_H__
#define __TRIDENTTD_ESP32NVS_H__

#include <Arduino.h>

extern "C" {
#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#ifdef TRIDENTTD_DEBUG_MODE
    #define DEBUG_PRINTER Serial
    #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
    #define DEBUG_PRINTF(fmt, args...) { DEBUG_PRINTER.printf(fmt,## args); }
#else
    #define DEBUG_PRINT(...) { }
    #define DEBUG_PRINTLN(...) { }
    #define DEBUG_PRINTF(fmt, args...) { }
#endif

#define VERSION_EXTRA

#ifdef VERSION_EXTRA
#include <esp_partition.h>
#endif


class TridentTD_ESP32NVS {
public:
  TridentTD_ESP32NVS();

  bool    begin();
  void    close();

  bool    eraseAll();
  bool    erase(String key);

  bool    setInt(String key, uint8_t value);
  bool    setInt(String key, int16_t value);
  bool    setInt(String key, uint16_t value);
  bool    setInt(String key, int32_t value);
  bool    setInt(String key, uint32_t value);
  bool    setInt(String key, int64_t value);
  bool    setInt(String key, uint64_t value);
  bool    setFloat(String key, float value);
  bool    setString(String key, String value);
  bool    setCharArray(String key, const char* value);
  bool    setObject(String key, void* object, size_t length);
  inline bool    setBool(String key, bool value)            { return setInt(key,(uint8_t)value); }   // V1.3 added ; V1.4 fixed cast to uint8_t

  int64_t getInt(String key);
  float   getFloat(String key);
  String  getString(String key);
  char*   getCharArray(String key, char* rev_data );
  void*   getObject(String key, void* blob );
  bool    getObject(String key, void* blob, size_t length);                                 // V1.3 added
  inline  bool getBool(String key)                          { return (bool)getInt(key); }   // V1.3 added

  bool    exists(String key);      //V.1.1 added

#ifdef VERSION_EXTRA
  void    listKeys();
#endif

//  bool    setDouble(String key, double value);
//  double  getDouble(String key);

private:
  nvs_handle  _nvs_handle;
  esp_err_t   _err;

  bool        commit();
  nvs_handle  get_nvs_handle();
  String      _version = "1.4";
};

extern TridentTD_ESP32NVS NVS;

#endif

