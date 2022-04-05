#define FASTLED_INTERNAL
#include <FastLED.h> // https://github.com/FastLED/FastLED

#define DATA_PIN 4
#define CLOCK_PIN 3

CRGB leds[NUM_LEDS];

void leds_init()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.println("Init leds");
  for(int i=0; i < NUM_LEDS;i++) {
    leds[i] = CRGB::Green; 
    delay(10); 
    FastLED.show();
  }
  for(int i=0; i < NUM_LEDS;i++) {
    leds[i] = CRGB::Black; 
    delay(10); 
    FastLED.show();
  }
  FastLED.clear();
}

int get_channel(byte* p, int s) {
  int v = (p[s] - '0')*100 + (p[s+1] - '0')*10 + (p[s+2] - '0');
  return v;
}

int set_leds(byte *payload, unsigned int length) {
  int nleds = (length/9);
  nleds = nleds > NUM_LEDS ? NUM_LEDS : nleds;
  for (int i = 0; i < nleds ; i++) {
      int s = i * 9;
      int r = get_channel(payload, s);
      int g = get_channel(payload, s+3);
      int b = get_channel(payload, s+6);
      //Serial.println(r);
      //Serial.println(g);
      //Serial.println(b);
      leds[i] = CRGB(r, g, b);
  }  
  FastLED.show();
  return nleds;
}

int set_leds_bytes(byte *payload, unsigned int length) {
  int nleds = (length/3);
  nleds = nleds > NUM_LEDS ? NUM_LEDS : nleds;
  for (int i = 0; i < nleds ; i++) {
      int s = i * 3;
      int r = payload[s]; 
      int g = payload[s+1]; 
      int b = payload[s+2]; 
      //Serial.println(r);
      //Serial.println(g);
      //Serial.println(b);
      leds[i] = CRGB(r, g, b);
  }  
  FastLED.show();
  return nleds;
}

void rotate_leds() {
  CRGB first_led = leds[0];
  for (int i = 0; i < NUM_LEDS-1; i++) {
    leds[i] = leds[i+1];
  }
  leds[NUM_LEDS-1] = first_led;  
  FastLED.show();
}
