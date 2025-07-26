#include <Arduino.h>

#include <TFTDisplay.h>
#include <SensorsModule.h>
#include <Utils.h>
#include <wifi_env.h>
#include <WiFi.h>
#include "time.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
struct tm localTimeinfo;

void updateLocalTime();
void setup_wifi();

TFTDisplay display;
SensorsModule sensors;

// Update loops time tracking
unsigned long updateLocalTimeTs{0};
unsigned long updateLocalTimeDt{10000};
unsigned long updateSensorsTs{0};
unsigned long updateSensorsDt{1000};

void setup(void)
{
  Serial.begin(115200);
  setup_wifi();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  Wire.begin();

  sensors.setup();

  display.begin();
}

void loop(void)
{
  if (CalcDt(updateLocalTimeTs) > updateLocalTimeDt)
  {
    updateLocalTimeTs = millis();
    updateLocalTime();
    display.updateTime(localTimeinfo.tm_hour, localTimeinfo.tm_min);
  }

  if (CalcDt(updateSensorsTs) > updateSensorsDt)
  {
    updateSensorsTs = millis();
    if (sensors.update())
    {
      display.updateIAQ(sensors.getIAQ());
      display.updateTemperature(sensors.getTemperature());
      display.updateHumidity(sensors.getHumidity());
      display.updateGas(sensors.getGas());
      display.updateCO2(sensors.getCO2());
      display.updateVOC(sensors.getVOC());
    }
  }
}

void setup_wifi(void)
{
  WiFi.begin(USER_WIFI_SSID, USER_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void updateLocalTime(void)
{
  Serial.println("updateLocalTime");
  if (!getLocalTime(&localTimeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  // calculate the seconds offset to get time close to an update time event
  long offset_ts = (localTimeinfo.tm_sec * 1000) % updateLocalTimeDt;
  if (updateLocalTimeTs > updateLocalTimeDt && offset_ts > 500)
  {
    updateLocalTimeTs = updateLocalTimeTs - offset_ts;
  }
}