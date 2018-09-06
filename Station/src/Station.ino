#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
extern "C" {
#include "user_interface.h"
}

#define STATION_ID  1

uint8_t TARGET[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Mobile Device MAC
uint8_t HOTSPOT[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //Wlan hotspot MAC
static int my_target_packets_counter = 0;
static float rssi = 0;
#include "./sniffing_functions.h"


IPAddress SERVER(192,168,111,1);
WiFiClient Station;


void setup() {
  Serial.begin(57600);
  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D0, HIGH);
  digitalWrite(D4, HIGH);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_promiscuous_rx_cb(Sniffing);
  
}

void loop() {
  rssi = 0;
  my_target_packets_counter = 0;
  wifi_promiscuous_enable(1);
  digitalWrite(D0, LOW);
  while(!my_target_packets_counter)
  {
    delay(1);
  }
  digitalWrite(D0, HIGH);
  unsigned long Time1 = millis();
  int i=0;
  while(i<4)
  {
    delay(200);
    digitalWrite(D0, LOW);
    delay(300);
    digitalWrite(D0, HIGH);
    ++i;
    //Sniffing for 2 seconds
  }
  wifi_promiscuous_enable(0);
  rssi /= (float)my_target_packets_counter;
  Serial.print("\nFinal = ");
  Serial.println((float)rssi,1);

  WiFi.begin("ESPServer", "ESP_123456");
  digitalWrite(D4, LOW);
  digitalWrite(D4, HIGH);
  while(!Station.connect(SERVER,8008))
  {
    delay(100);
  }
  
  Station.write(STATION_ID);
  Station.println(rssi);
  Station.write('C');
  while(Station.connected()) delay(1);
  WiFi.disconnect();
  digitalWrite(D0, LOW);
  digitalWrite(D4, LOW);
  delay(1000);
  digitalWrite(D0, HIGH);
  digitalWrite(D4, HIGH);
  unsigned long Time2 = millis();
  while((Time2 - Time1) < 30000) { Time2 = millis(); delay(1); }
}

