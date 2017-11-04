#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
/* Test NodeMCU as a web server for configuring
 *  DK 04/11/17
 *  
 */

const char *ssid = "arduino-er";
const char *password = "password";

ESP8266WebServer server(80);

char* htmlBody_help = "<h1>Help</h1><br/>\n"
  "Visit http://192.168.4.1/ to access web server.<br/>\n"
  "Visit http://192.168.4.1/help to access this page.<br/>\n";

void handleRoot() {
    server.send(200, "text/html", "<h1>Hello! from arduino-er!</h1>");
}

void handleHelp(){
  server.send(200, "text/html", htmlBody_help);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/help", handleHelp);
    server.begin();
    Serial.println("HTTP server beginned");
}

void loop() {
  // put your main code here, to run repeatedly:
  // scan for existing networks:
  //Serial.println("Scanning available networks...");
  //listNetworks();
  //delay(10000);
    server.handleClient();
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printEncryptionType(int thisType) 
{
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}
