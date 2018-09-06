





uint8_t *getFrameSource(uint8_t*);
uint8_t *getFrameBSSID(uint8_t*);
void Sniffing(uint8_t *buf, uint16_t len)
{
  if(len != 12  &&  len != 128) {
      if(!memcmp(getFrameSource(buf),TARGET,6) && !memcmp(getFrameBSSID(buf),HOTSPOT,6))
      {
          my_target_packets_counter  += 1;
          rssi += (float(buf[0]) - 256) / 0.9999 ;
      }
  } 
}

uint8_t *getFrameSource(uint8_t *buf)
{
  uint8_t *FrameSource=NULL;
  uint8_t ds = buf[13] & 3;
  if(ds == 0 || ds == 1) FrameSource= buf + 22;
  else FrameSource= buf + 16;
  return FrameSource;
}

uint8_t *getFrameBSSID(uint8_t *buf)
{
  uint8_t *FrameBSSID=NULL;
  uint8_t ds = buf[13] & 3;
  if(ds == 0) FrameBSSID= buf + 28;
  else if(ds == 1) FrameBSSID= buf + 16;
  else FrameBSSID= buf + 22;
  return FrameBSSID;
}

