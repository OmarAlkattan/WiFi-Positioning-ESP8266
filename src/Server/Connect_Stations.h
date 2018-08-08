WiFiServer server(8008);



bool Client_Registered(WiFiClient,WiFiClient[]);


void Get_Rss_Stations(point *p)
{
  int i=0;
  WiFiClient Stations[STATIONS_NUM];
  while(i<STATIONS_NUM)
  {
    
     WiFiClient cl = server.available();
     if(cl)
     {
        if(!Client_Registered(cl,Stations))
        {
          Stations[i] = cl;
          while(!Stations[i].available())  delay(1);
          char Station_ID = Stations[i].read();
          String RssiStr = Stations[i].readStringUntil('C');
          p->rss[Station_ID-1] = RssiStr.toFloat() / 1.000;
          while(Stations[i].available())  char c = Stations[i].read();
          Stations[i].stop();
          ++i;
        }
        else cl.stop();
     }
  }
}


bool Client_Registered(WiFiClient cl,WiFiClient Stations[]) 
{
  for(int i=0;i<STATIONS_NUM;++i)
  {
    if(Stations[i]!=NULL && cl.remoteIP()==Stations[i].remoteIP()) return 1;
  }
  return 0;
}

