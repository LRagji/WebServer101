/*
  WebServer101.h - Library for better handling on web request and easy of use.
  Created by Laukik Ragji, December 03, 2016.
  Released with MIT.
*/

#ifndef WebServer101_h
#define WebServer101_h

#include "Arduino.h"
#include <WiFi101.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

class WebServer101
{
public:
  WebServer101();
  void ProcessRequest(WiFiServer &server, void (*handleRequest)(String operation, String path, String headerValue, WiFiClient &client), String headerName);
  String GenerateHeader(String key, String value, bool lastHeader);
  String GenerateReponseStatusLine(int code);
private:
 String ResponseCodeToString(int code);
};

#endif
