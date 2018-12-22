// TridentTD_TridentTD_ESP32NVS.h

// Copyright (c) 2016-2018 TridentTD

// History : 
// V.1.0  @ 21/11/2560 Buddism Era ( 2017 )   by TridentTD
//        First release
// V.1.1  @ 22/12/2561 Buddism Era ( 2018 )   by TridentTD
//        Support isExist() for checking key is exist on NVS or not?

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

  int64_t getInt(String key);
  float   getFloat(String key);
  String  getString(String key);
  char*   getCharArray(String key);
  void*   getObject(String key);

  bool    exists(String key);      //V.1.1 added

//  bool    setDouble(String key, double value);
//  double  getDouble(String key);

private:
  nvs_handle  _nvs_handle;
  esp_err_t   _err;

  bool        commit();
  nvs_handle  get_nvs_handle();
  String      _version = "1.1";
};

extern TridentTD_ESP32NVS NVS;

#endif

