/**
 * @file streams-url_mp3-out.ino
 * @author Phil Schatzmann
 * @brief read MP3 stream from url and output metadata
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 */

// set this in AudioConfig.h or here after installing https://github.com/pschatzmann/arduino-libhelix.git
#define USE_HELIX 

#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"

using namespace audio_tools;  

ICYStream url("ssid","password");
MetaDataPrint out; // final output of decoded stream
StreamCopy copier(out, url); // copy url to decoder

// callback for meta data
void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

// mp3 radio
  url.httpRequest().header().put("Icy-MetaData","1");
  url.begin("https://centralcharts.ice.infomaniak.ch/centralcharts-128.mp3","audio/mp3");

  out.setCallback(printMetaData);
  out.begin(url.httpRequest());
}

void loop(){
  copier.copy();
}