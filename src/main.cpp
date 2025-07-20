#include <Arduino.h>

#include <TFTDisplay.h>
#include <SensorsModule.h>

TFTDisplay display;
SensorsModule sensors;

int hour = 3;
int minute = 0;

void setup(void)
{
  Serial.begin(115200);

  Wire.begin();
  sensors.setup();

  display.begin();
}

void loop(void)
{
  // TODO: get time from NTP server,
  // then convert into a long (HH*60*60 + MM*60) and save as local_hh_mm
  // save the SS*1000 into time_offset_ms
  // then store it in a varible local_time_ms
  // On every loop, (millis() + time_offset_ms) %(60*1000) != local_hh_mm
  // if yes,update display with local_hh_mm

  // Temporary simulation of time to show on display
  if (minute + 1 > 59)
  {
    hour = (hour + 1) % 23;
  }
  minute = (minute + 1) % 60;
  
  display.updateTime(hour, minute);
  
  // Update all sensors fields on the display if the sensor reading was successfull
  if (sensors.update()){
    display.updateIAQ(sensors.getIAQ());
    display.updateTemperature(sensors.getTemperature());
    display.updateHumidity(sensors.getHumidity());
    display.updateGas(sensors.getGas());
    display.updateCO2(sensors.getCO2());
    display.updateVOC(sensors.getVOC());
  }

  // Simple ~1s to simulate sample/update frequency
  delay(1000);
}