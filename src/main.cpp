#include <Arduino.h>
// #include <bsec2.h>
#include <TFTDisplay.h>

TFTDisplay display;
int hour=0;
int minute=0;
/* Entry point for the example */
void setup(void)
{
  display.begin();
  Serial.begin(115200);
}

/* Function that is looped forever */
void loop(void)
{
  // TODO: get time from NTP server, 
  // then convert into a long (HH*60*60 + MM*60) and save as local_hh_mm
  // save the SS*1000 into time_offset_ms
  // then store it in a varible local_time_ms
  // On every loop, (millis() + time_offset_ms) %(60*1000) != local_hh_mm
  // if yes,update display with local_hh_mm
  
  if(minute + 1 > 59){
    hour = (hour +1)%23;
  } 

  minute = (minute +1)%60;

  display.updateTime(hour,minute);
  display.updateIAQ((float)minute);
  display.updateTemperature((float)(minute-30));
  display.updateHumidity((float)minute);
  display.updateGas((float)minute);
  display.updateCO2((float)minute);
  display.updateVOC((float)minute);
  delay(100);
}