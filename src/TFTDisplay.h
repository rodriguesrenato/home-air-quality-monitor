#ifndef TFTDISPLAY_H
#define TFTDISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <time.h>

typedef struct
{
    int w;
    int h;
    int size;
} uiTextCfg;

typedef struct
{
    int w1;
    int w2;
    int h;
    int size;
} uiHLineCfg;

typedef struct
{
    uiTextCfg time = {25, 5, 3};
    uiHLineCfg bar1 = {0, 135, 353};
    uiTextCfg iaqLabel = {1, 50, 2};
    uiTextCfg iaqVal = {63, 50, 3};

    uiTextCfg temperatureLabel = {1, 91, 2};
    uiTextCfg temperatureVal = {63, 91, 3};
    uiTextCfg temperatureValLabel = {120, 97, 2};

    uiTextCfg humidityLabel = {1, 132, 2};
    uiTextCfg humidityVal = {63, 132, 3};
    uiTextCfg humidityValLabel = {120, 138, 2};

    uiTextCfg gasLabel = {1, 173, 2};
    uiTextCfg gasVal = {63, 173, 3};
    uiTextCfg gasValLabel = {120, 179, 2};

    uiTextCfg co2Label = {1, 214, 1};
    uiTextCfg co2Val = {23, 214, 2};

    uiTextCfg vocLabel = {76, 214, 1};
    uiTextCfg vocVal = {99, 214, 2};

} uiDefs;

class TFTDisplay
{
public:
    TFTDisplay();
    void begin();
    void drawStaticUI();
    void drawLabels();
    void updateTime(int hour, int minute);
    void updateIAQ(float iaq);
    void updateTemperature(float temperature);
    void updateHumidity(float humidity);
    void updateGas(float gas_resistance);
    void updateCO2(float co2_ppm);
    void updateVOC(float voc_ppm);

private:
    Adafruit_ST7789 tft;
    uiDefs uidata;
    static const int screenWidth = 135;
    static const int screenHeight = 240;
    static const int timeBarHeight = 20;
    static const int numRows = 5;
    static const int rowHeight = (screenHeight - timeBarHeight) / numRows;
};

#endif