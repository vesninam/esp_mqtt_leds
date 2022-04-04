#include <PubSubClient.h>

PubSubClient mqtt_cli(wifiClient);

int get_int(byte* p, int s) {
  int v = (p[s] - '0')*100 + (p[s+1] - '0')*10 + p[s+2];
  return v;
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("With length: ");
    Serial.println(length);    
    if (strcmp(topic, "lab/leds/strip/set_leds") == 0) {
      int nleds = set_leds(payload, length);
      Serial.print("Set color for leds ");
      Serial.println(nleds);
    }
    if (strcmp(topic, "lab/leds/strip/rotate_leds") == 0) {
      rotate_leds();
    }
    Serial.println("-----------------------");
}

void MQTT_init(){
  mqtt_cli.setServer(mqtt_broker, mqtt_port);
  mqtt_cli.setBufferSize(2048);
  mqtt_cli.setCallback(callback);
  while (!mqtt_cli.connected()) {
      String client_id = "esp8266-" + String(WiFi.macAddress());
      Serial.print("The client " + client_id);
      Serial.println(" connects to the public mqtt broker\n");
      if (mqtt_cli.connect(client_id.c_str())){
          Serial.println("MQTT Connected");
      } else {
          Serial.print("failed with state ");
          Serial.println(mqtt_cli.state());
          delay(2000);
      }
  }  
}
