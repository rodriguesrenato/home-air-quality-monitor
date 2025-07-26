#ifndef SENSORSMODULE_H
#define SENSORSMODULE_H

#include <bsec2.h>

#define SAMPLE_RATE		BSEC_SAMPLE_RATE_CONT

class SensorsModule
{
public:
    SensorsModule();
    void setup();
    bool update();
    float getIAQ();
    float getTemperature();
    float getHumidity();
    float getGas();
    float getCO2();
    float getVOC();
    int getBsecStatus();
    int getBme68xStatus();
private:
    Bsec2 envSensor_;
    void checkBsecStatus(Bsec2 bsec);
    bool readSensors();
    bool parseSensorsData();
    float iaq_{};
    float iaq_accuracy_{};
    float raw_temperature_{};
    float raw_pressure_{};
    float raw_humidity_{};
    float raw_gas_{};
    float stabilization_status_{};
    float run_in_status_{};
    float sensor_heat_compensated_temperature_{};
    float sensor_heat_compensated_humidity_{};
    float static_iaq_{};
    float co2_equivalent_{};
    float breath_voc_equivalent_{};
    float gas_percentage_{};
    float compensated_gas_{};
    int bsec_status_{};
    int bme68x_status_{};
};
#endif