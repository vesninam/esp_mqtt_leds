#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;    
WiFiClient wifiClient;

String ip = "(IP unset)"; 

String id(){

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return macID;
}

bool StartAPMode() {
  Serial.println("Try WiFi in AP mode with name: "+ ssidAP + " " + id());
  IPAddress apIP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP((ssidAP + " " + id()).c_str(), passwordAP.c_str());
  Serial.println("");
  Serial.println("WiFi up in AP mode with name: "+ ssidAP + " " + id());
  return true;
}

void StartCLIMode() {
  Serial.println("Try WiFi in CLIENT mode ");
  wifiMulti.addAP(ssidCLI, passwordCLI);
  //it is possible to add more networks to connect
  while(wifiMulti.run() != WL_CONNECTED) {
       
  }
  Serial.println("WiFi in CLIENT mode ");
}

void WIFI_init(bool mode_ap) {
    if (mode_ap) {
      StartAPMode();
      ip = WiFi.softAPIP().toString();
    } else {
      StartCLIMode();
      ip = WiFi.localIP().toString();
    }
    Serial.println("IP address: ");
    Serial.println(ip);  
}
