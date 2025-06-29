#include "TFTDisplay.h"

TFTDisplay::TFTDisplay()
    : tft(TFT_CS, TFT_DC, TFT_RST) {}

void TFTDisplay::begin()
{
    pinMode(TFT_BACKLITE, OUTPUT);
    digitalWrite(TFT_BACKLITE, HIGH);

    // turn on the TFT / I2C power supply
    pinMode(TFT_I2C_POWER, OUTPUT);
    digitalWrite(TFT_I2C_POWER, HIGH);
    delay(10);

    tft.init(135, 240);
    tft.setRotation(0); // Portrait mode
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextWrap(false);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);

    drawLabels();
}

void TFTDisplay::drawLabels()
{
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);

    // Line divider under the time
    for (int i = 0; i < uidata.bar1.size; i++)
    {
        tft.drawLine(uidata.bar1.w1, uidata.bar1.h + i, uidata.bar1.w2, uidata.bar1.h + i, ST77XX_WHITE);
    }

    // IAQ
    tft.setTextSize(uidata.iaqLabel.size);
    tft.setCursor(uidata.iaqLabel.w, uidata.iaqLabel.h);
    tft.print("IAQ");
    tft.setTextSize(uidata.iaqVal.size);
    tft.setCursor(uidata.iaqVal.w, uidata.iaqVal.h);
    tft.print("500");

    // TEMP
    tft.setTextSize(uidata.temperatureLabel.size);
    tft.setCursor(uidata.temperatureLabel.w, uidata.temperatureLabel.h);
    tft.print("TEMP");
    tft.setTextSize(uidata.temperatureVal.size);
    tft.setCursor(uidata.temperatureVal.w, uidata.temperatureVal.h);
    tft.print("-00");
    tft.setTextSize(uidata.temperatureValLabel.size);
    tft.setCursor(uidata.temperatureValLabel.w, uidata.temperatureValLabel.h);
    tft.print("C");

    // HUM
    tft.setTextSize(uidata.humidityLabel.size);
    tft.setCursor(uidata.humidityLabel.w, uidata.humidityLabel.h);
    tft.print("HUM");
    tft.setTextSize(uidata.humidityVal.size);
    tft.setCursor(uidata.humidityVal.w, uidata.humidityVal.h);
    tft.print("000");
    tft.setTextSize(uidata.humidityValLabel.size);
    tft.setCursor(uidata.humidityValLabel.w, uidata.humidityValLabel.h);
    tft.print("%");

    // GAS
    tft.setTextSize(uidata.gasLabel.size);
    tft.setCursor(uidata.gasLabel.w, uidata.gasLabel.h);
    tft.print("GAS");
    tft.setTextSize(uidata.gasVal.size);
    tft.setCursor(uidata.gasVal.w, uidata.gasVal.h);
    tft.print("000");
    tft.setTextSize(uidata.gasValLabel.size);
    tft.setCursor(uidata.gasValLabel.w, uidata.gasValLabel.h);
    tft.print("%");

    // CO2
    tft.setTextSize(uidata.co2Label.size);
    tft.setCursor(uidata.co2Label.w, uidata.co2Label.h);
    tft.print("CO2");
    tft.setTextSize(uidata.co2Val.size);
    tft.setCursor(uidata.co2Val.w, uidata.co2Val.h);
    tft.print("0000");

    // VOC
    tft.setTextSize(uidata.vocLabel.size);
    tft.setCursor(uidata.vocLabel.w, uidata.vocLabel.h);
    tft.print("VOC");
    tft.setTextSize(uidata.vocVal.size);
    tft.setCursor(uidata.vocVal.w, uidata.vocVal.h);
    tft.print("0.0");
}

void TFTDisplay::updateTime(int hour, int minute)
{
    tft.setTextSize(uidata.time.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.time.w, uidata.time.h); // Centered horizontally (approx)
    tft.printf("%02d:%02d", hour, minute);
}

void TFTDisplay::updateIAQ(float iaq)
{
    tft.setTextSize(uidata.iaqVal.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.iaqVal.w, uidata.iaqVal.h); // Centered horizontally (approx)
    tft.printf("%3.0f", iaq);
}

void TFTDisplay::updateTemperature(float temperature)
{
    tft.setTextSize(uidata.temperatureVal.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.temperatureVal.w, uidata.temperatureVal.h); // Centered horizontally (approx)
    tft.printf((temperature < 0) ? "%+3.0f" : "%3.0f", temperature);
}

void TFTDisplay::updateHumidity(float humidity)
{
    tft.setTextSize(uidata.humidityVal.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.humidityVal.w, uidata.humidityVal.h); // Centered horizontally (approx)
    tft.printf("%3d", (int)humidity);
}

void TFTDisplay::updateGas(float gas_resistance)
{
    tft.setTextSize(uidata.gasVal.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.gasVal.w, uidata.gasVal.h); // Centered horizontally (approx)
    tft.printf("%3d", (int)gas_resistance);
}

void TFTDisplay::updateCO2(float co2_ppm)
{
    tft.setTextSize(uidata.co2Val.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.co2Val.w, uidata.co2Val.h); // Centered horizontally (approx)
    tft.printf("%4.0f", co2_ppm);
}

void TFTDisplay::updateVOC(float voc_ppm)
{
    tft.setTextSize(uidata.vocVal.size);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.setCursor(uidata.vocVal.w, uidata.vocVal.h); // Centered horizontally (approx)
    tft.printf("%01.1f", voc_ppm);
}
