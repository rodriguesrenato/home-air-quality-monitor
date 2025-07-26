#include "SensorsModule.h"

SensorsModule::SensorsModule()
{
}

void SensorsModule::setup()
{
    /* Desired subscription list of BSEC2 outputs */
    bsecSensor sensorList[] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_STABILIZATION_STATUS,
        BSEC_OUTPUT_RUN_IN_STATUS,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
        BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_GAS_PERCENTAGE,
        BSEC_OUTPUT_COMPENSATED_GAS};
    /* Initialize the library and interfaces */
    if (!envSensor_.begin(BME68X_I2C_ADDR_HIGH, Wire))
    {
        checkBsecStatus(envSensor_);
    }

    /*
     *	The default offset provided has been determined by testing the sensor in LP and ULP mode on application board 3.0
     *	Please update the offset value after testing this on your product
     */
    if (SAMPLE_RATE == BSEC_SAMPLE_RATE_ULP)
    {
        envSensor_.setTemperatureOffset(TEMP_OFFSET_ULP);
    }
    else if (SAMPLE_RATE == BSEC_SAMPLE_RATE_LP)
    {
        envSensor_.setTemperatureOffset(TEMP_OFFSET_LP);
    }

    /* Subsribe to the desired BSEC2 outputs */
    if (!envSensor_.updateSubscription(sensorList, ARRAY_LEN(sensorList), SAMPLE_RATE))
    {
        checkBsecStatus(envSensor_);
    }

    Serial.println("BSEC library version " +
                   String(envSensor_.version.major) + "." + String(envSensor_.version.minor) + "." + String(envSensor_.version.major_bugfix) + "." + String(envSensor_.version.minor_bugfix));
}

bool SensorsModule::update()
{
    return readSensors();
}

/*
    Return True if successfully read the sensors, false otherwise
*/
bool SensorsModule::readSensors()
{
    Serial.println("Try to read");
    bool success{false};
    if (envSensor_.run())
    {
        success = parseSensorsData();
    }
    else
    {
        checkBsecStatus(envSensor_);
    }

    // Update library and sensor status
    bsec_status_ = envSensor_.status;
    bme68x_status_ = envSensor_.sensor.status;
    return success;
}

bool SensorsModule::parseSensorsData()
{
    const bsecOutputs *outputs = envSensor_.getOutputs();
    if (outputs == nullptr)
    {
        return false;
    }
    if (!outputs->nOutputs)
    {
        return false;
    }

    for (uint8_t i = 0; i < outputs->nOutputs; i++)
    {
        const bsecData output = outputs->output[i];
        switch (output.sensor_id)
        {
        case BSEC_OUTPUT_IAQ:
            iaq_ = output.signal;
            iaq_accuracy_ = output.accuracy;
            break;
        case BSEC_OUTPUT_RAW_TEMPERATURE:
            raw_temperature_ = output.signal;
            break;
        case BSEC_OUTPUT_RAW_PRESSURE:
            raw_pressure_ = output.signal;
            break;
        case BSEC_OUTPUT_RAW_HUMIDITY:
            raw_humidity_ = output.signal;
            break;
        case BSEC_OUTPUT_RAW_GAS:
            raw_gas_ = output.signal;
            break;
        case BSEC_OUTPUT_STABILIZATION_STATUS:
            stabilization_status_ = output.signal;
            break;
        case BSEC_OUTPUT_RUN_IN_STATUS:
            run_in_status_ = output.signal;
            break;
        case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE:
            sensor_heat_compensated_temperature_ = output.signal;
            break;
        case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY:
            sensor_heat_compensated_humidity_ = output.signal;
            break;
        case BSEC_OUTPUT_STATIC_IAQ:
            static_iaq_ = output.signal;
            break;
        case BSEC_OUTPUT_CO2_EQUIVALENT:
            co2_equivalent_ = output.signal;
            break;
        case BSEC_OUTPUT_BREATH_VOC_EQUIVALENT:
            breath_voc_equivalent_ = output.signal;
            break;
        case BSEC_OUTPUT_GAS_PERCENTAGE:
            gas_percentage_ = output.signal;
            break;
        case BSEC_OUTPUT_COMPENSATED_GAS:
            compensated_gas_ = output.signal;
            break;
        default:
            break;
        }
    }

    return true;
}

void SensorsModule::checkBsecStatus(Bsec2 bsec)
{
    if (bsec.status < BSEC_OK)
    {
        Serial.println("BSEC error code : " + String(bsec.status));
    }
    else if (bsec.status > BSEC_OK)
    {
        Serial.println("BSEC warning code : " + String(bsec.status));
    }

    if (bsec.sensor.status < BME68X_OK)
    {
        Serial.println("BME68X error code : " + String(bsec.sensor.status));
    }
    else if (bsec.sensor.status > BME68X_OK)
    {
        Serial.println("BME68X warning code : " + String(bsec.sensor.status));
    }
}

float SensorsModule::getIAQ()
{
    return iaq_;
}

float SensorsModule::getTemperature()
{
    return raw_temperature_;
}

float SensorsModule::getHumidity()
{
    return raw_humidity_;
}

float SensorsModule::getGas()
{
    return gas_percentage_;
}

float SensorsModule::getCO2()
{
    return co2_equivalent_;
}

float SensorsModule::getVOC()
{
    return breath_voc_equivalent_;
}

int SensorsModule::getBsecStatus()
{
    return bsec_status_;
}

int SensorsModule::getBme68xStatus()
{
    return bme68x_status_;
}