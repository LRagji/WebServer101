/*
  WebServer101.cpp - Library for better handling on web request and easy of use.
  Created by Laukik Ragji, December 03, 2016.
  Released with MIT.
*/

#include "Arduino.h"
#include <WiFi101.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "WebServer101.h"

WebServer101::WebServer101()
{
}

void WebServer101::ProcessRequest(WiFiServer &server, void(*handleRequest)(String operation, String path, String headerValue, WiFiClient &client), String headerName)
{
  byte RequestLineNumber = 0;
  WiFiClient client = server.available();
  if (client) {                             // if you get a client,
    //Serial.println("new client");           // print a message out the serial port
    String requestPath = "";
    String reuestOperation = "";
    String currentLine = "";                // make a String to hold incoming data from the client
    String headerValue = "";
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            if (reuestOperation != "" && reuestOperation != "")
            {
              //Start Sending Response from here
              //              Serial.print("Respond to: ");
              //              Serial.print("OP:" + reuestOperation);
              //              Serial.println(" PATH:" + requestPath);
              //String reponse;
              reuestOperation.trim();
              requestPath.trim();
              headerValue.trim();
              handleRequest(reuestOperation, requestPath, headerValue, client);
              //client.print(reponse);
            }
            else
            {
              client.print(GenerateReponseStatusLine(404));
              client.print(GenerateHeader("Connection", "close", true));
            }
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            //Serial.print(RequestLineNumber);
            //Serial.println(" " + currentLine);
            if (RequestLineNumber == 0) //No Appropiate Method found to invoke check if any method matches
            {
              int startSpaceIndex = currentLine.indexOf(' ');
              int endSpaceIndex = currentLine.lastIndexOf(' ');
              if (startSpaceIndex != -1 & endSpaceIndex != -1)
              {
                reuestOperation  = currentLine.substring(0, startSpaceIndex);
                requestPath = currentLine.substring(startSpaceIndex, endSpaceIndex);
              }
            }
            else if (reuestOperation != "" && reuestOperation != "" && currentLine.startsWith(headerName))
            {
              int seperatorIndex = currentLine.indexOf(':');
              if (seperatorIndex != -1)
              {
                seperatorIndex += 1;
                if (seperatorIndex < currentLine.length())
                {
                  headerValue = currentLine.substring(seperatorIndex);
                }
              }
            }
            currentLine = "";
            RequestLineNumber++;
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
  }
}

String WebServer101::GenerateHeader(String key, String value, bool lastHeader)
{
  if (lastHeader)
  {
    return key + ":" + value + "\r\n\r\n";
  }
  else
  {
    return key + ":" + value + "\r\n";
  }
}

String WebServer101::GenerateReponseStatusLine(int code)
{
  return "HTTP/1.1 " + String(code) + " " + ResponseCodeToString(code) + "\r\n";
}

String WebServer101::ResponseCodeToString(int code) 
{
  switch (code) {
    case 100: return F("Continue");
    case 101: return F("Switching Protocols");
    case 200: return F("OK");
    case 201: return F("Created");
    case 202: return F("Accepted");
    case 203: return F("Non-Authoritative Information");
    case 204: return F("No Content");
    case 205: return F("Reset Content");
    case 206: return F("Partial Content");
    case 300: return F("Multiple Choices");
    case 301: return F("Moved Permanently");
    case 302: return F("Found");
    case 303: return F("See Other");
    case 304: return F("Not Modified");
    case 305: return F("Use Proxy");
    case 307: return F("Temporary Redirect");
    case 400: return F("Bad Request");
    case 401: return F("Unauthorized");
    case 402: return F("Payment Required");
    case 403: return F("Forbidden");
    case 404: return F("Not Found");
    case 405: return F("Method Not Allowed");
    case 406: return F("Not Acceptable");
    case 407: return F("Proxy Authentication Required");
    case 408: return F("Request Time-out");
    case 409: return F("Conflict");
    case 410: return F("Gone");
    case 411: return F("Length Required");
    case 412: return F("Precondition Failed");
    case 413: return F("Request Entity Too Large");
    case 414: return F("Request-URI Too Large");
    case 415: return F("Unsupported Media Type");
    case 416: return F("Requested range not satisfiable");
    case 417: return F("Expectation Failed");
    case 500: return F("Internal Server Error");
    case 501: return F("Not Implemented");
    case 502: return F("Bad Gateway");
    case 503: return F("Service Unavailable");
    case 504: return F("Gateway Time-out");
    case 505: return F("HTTP Version not supported");
    default:  return "";
  }
}
