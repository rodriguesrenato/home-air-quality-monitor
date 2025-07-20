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
    
private:
    Bsec2 envSensor;
    void checkBsecStatus(Bsec2 bsec);
    bool readSensors();
    float iaq{};
    float iaq_accuracy{};
    float raw_temperature{};
    float raw_pressure{};
    float raw_humidity{};
    float raw_gas{};
    float stabilization_status{};
    float run_in_status{};
    float sensor_heat_compensated_temperature{};
    float sensor_heat_compensated_humidity{};
    float static_iaq{};
    float co2_equivalent{};
    float breath_voc_equivalent{};
    float gas_percentage{};
    float compensated_gas{};
};
#endif