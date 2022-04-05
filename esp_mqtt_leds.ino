#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "leds.h"
#include "MQTT.h"


void setup(void){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  for(int i=0; i< 3; i++) {
    digitalWrite(led, !digitalRead(led));
    delay(500);
  }
  leds_init();
  WIFI_init(false);
  server_init();
  MQTT_init();
  mqtt_cli.publish("lab/leds/strip/state", "hello emqx");
  mqtt_cli.subscribe("lab/leds/strip/set_leds");
  mqtt_cli.subscribe("lab/leds/strip/set_leds_byte");
  mqtt_cli.subscribe("lab/leds/strip/rotate_leds");
  
}

void loop(void){
  server.handleClient();                   
  mqtt_cli.loop();
}
