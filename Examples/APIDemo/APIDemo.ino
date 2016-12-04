#include <WebServer101.h>
#include <WiFi101.h>
#include <WiFiClient.h>
#include <WiFiServer.h>


char ssid[] = "******";     //  your network SSID (name)
char pass[] = "*****";   // your network password
WiFiServer WebServer(80);
WebServer101 ws101;
void setup() {

  Serial.begin(115200);
  while (!Serial);

  InitNetwork();

  WebServer.begin();

  Serial.println("Server Ready to accept requests");
}



void InitNetwork()
{
  Serial.print("Initializing Network...");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("failed, WiFi shield not present");
    // don't continue:
    while (true);
  }
  Serial.println("completed");

  Connect(3);
}

void Connect(byte maxTries)
{
  int status = 0;
  byte tries = 0;
  while ( status != WL_CONNECTED & tries < maxTries) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
    tries++;
  }
  if (status != WL_CONNECTED & tries >= maxTries)
  {
    Serial.println("No Network Found");
  }
  else
  {
    printWifiStatus();
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop() {

  ws101.ProcessRequest(WebServer, requestHandler, "Laukik");

}

void requestHandler(String operation, String path, String headerValue, WiFiClient &client)
{

  Serial.print("Respond to: ");
  Serial.print("OP:" + operation);
  Serial.print(" PATH:" + path);
  Serial.println(" With :" + headerValue);

  client.print(ws101.GenerateReponseStatusLine(404));
  client.print(ws101.GenerateHeader("Connection", "close", true));

  //  char reponseBuff[responseString.length()];
  //  responseString.toCharArray(reponseBuff, responseString.length());
  //  Serial.println(reponseBuff);
  //  return reponseBuff;
}
