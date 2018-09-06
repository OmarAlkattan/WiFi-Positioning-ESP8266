#include <ESP8266WiFi.h>
#include <WiFiClient.h>
extern "C" {
#include "user_interface.h"
}


#define STATIONS_NUM    4
#define REFERENCES_NUM  4
#define REFERENCES_NUM_ON_X     2
#define REFERENCES_NUM_ON_Y     2
#define REFERENCES_SAMPLING_STEP 2
#define ELECTED_REFERENCE_POINTS  2
const char *ssid = "ESPServer";
const char *password = "ESP_123456";



struct point
{
  float x,y;
  float rss[STATIONS_NUM];
}static Database[REFERENCES_NUM];

static float Distance[2][REFERENCES_NUM];

#include "./Connect_Stations.h"

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D0, HIGH);
  digitalWrite(D4, HIGH);
  Serial.begin(57600);
  initWiFi();
  server.begin();
  server.setNoDelay(true);
  /**************************************/
  digitalWrite(D0, LOW);
  OfflineMode();
  digitalWrite(D0, HIGH);
  /*************************************/
}


void loop() {
  point P;
  /*****************************************/
  digitalWrite(D4, LOW);
  P = OnlineMode();
  digitalWrite(D4, HIGH);
  /*****************************************/
  Serial.println("Point Coordinates :");
  Serial.print("x = ");
  Serial.println(P.x);
  Serial.print("y = ");
  Serial.println(P.y);
}


void initWiFi(void) {

  IPAddress Ip;
  IPAddress NMask(255, 255, 255, 0);

  WiFi.mode(WIFI_AP);
  Ip.fromString("192.168.111.1");

  WiFi.softAP(ssid,password);
  WiFi.softAPConfig(Ip, Ip, NMask);     
}


void OfflineMode()
{
  for(int i=0;i<REFERENCES_NUM;++i)
  {
    Database[i].x = int(i % REFERENCES_NUM_ON_X)* REFERENCES_SAMPLING_STEP / 1.00;
    Database[i].y = int(i / REFERENCES_NUM_ON_Y)* REFERENCES_SAMPLING_STEP / 1.00;
    Get_Rss_Stations(&Database[i]);
    Serial.print(".....................................................\n ");
    Serial.print("Calibrated point coords:\n ");
    Serial.println(Database[i].x,2);
    Serial.println(Database[i].y,2);
    Serial.print("Calibration results:\n ");
    for(int k=0;k<STATIONS_NUM;++k) { 
        Serial.printf("Station %d = ",k+1);
        Serial.println(Database[i].rss[k],2);
    }
  }
}


point OnlineMode()
{
  point P;
  P.x = 0.00000;
  P.y = 0.00000;
  
  Get_Rss_Stations(&P);
  Serial.println("UP's rssi :");
  for(int k=0;k<STATIONS_NUM;++k) {
    Serial.printf("Station %d = ",k+1);
    Serial.println(P.rss[k],2);
  }
  
  Manhatten_Distance(P);
  Sorting_Distances();
  Find_Point_Coordinate(&P);
  return P;
}

void Manhatten_Distance(point P)
{
  for(int i=0;i<REFERENCES_NUM;++i)
  {
    Distance[0][i] = 0.0000;
    Distance[1][i] = i;
    for(int k=0;k<STATIONS_NUM;++k)
    {
      Distance[0][i] += fabs(P.rss[k]  - Database[i].rss[k]);
    }
  }
}

void Sorting_Distances()
{
  float f;
  for(int i=1;i<REFERENCES_NUM;++i)
  {
    int j=i;
    while(Distance[0][j] < Distance[0][j-1])
    {
      f = Distance[0][j];
      Distance[0][j] = Distance[0][j-1];
      Distance[0][j-1] = f;

      f = Distance[1][j];
      Distance[1][j] = Distance[1][j-1];
      Distance[1][j-1] = f;
      --j;
      if(j == 0) break;
    }
  }
}

void Find_Point_Coordinate(point* P)
{
  float Div = 0.000000;
  for(int i=0;i<ELECTED_REFERENCE_POINTS;++i)
  {
    P->x += (1.0000/Distance[0][i])*Database[(int)Distance[1][i]].x;
    P->y += (1.0000/Distance[0][i])*Database[(int)Distance[1][i]].y;
    Div += 1.0000/Distance[0][i];
  }
  P->x /= Div;
  P->y /= Div;
}

