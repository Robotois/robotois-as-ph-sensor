/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhSensor.h
 * Author: yovany
 *
 * Created on May 25, 2018, 10:36 AM
 */

#ifndef PHSENSOR_H
#define PHSENSOR_H

#include <stdint.h>
#include <string>
#include <bcm2835.h>

#define DEFAULT_ADDRESS 0x63
#define MID_CALIBRATION 0x00
#define LOW_CALIBRATION 0x01
#define HIGH_CALIBRATION 0x02

class PhSensor {
public:
    PhSensor(uint8_t addr = 0x00);
    PhSensor(const PhSensor& orig);
    virtual ~PhSensor();
    
    float reading();
    bool deviceInfo();
    void tempCompensation(float temp);
    void calibrate(uint8_t point, float phValue);
private:
    uint8_t addr;
    char rBuf[20],wBuf[20];
    void bcm_init();
    void bcm_end();
    void selectModule();
    std::string calibrateString(uint8_t point);

};

#endif /* PHSENSOR_H */

