/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   PhSensor.cpp
 * Author: yovany
 *
 * Created on May 25, 2018, 10:36 AM
 */

#include "PhSensor.h"
#include <bcm2835.h>
#include <stdint.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <exception>
#include <thread>
#include <chrono>

PhSensor::PhSensor(uint8_t _addr) {
    if (_addr > 1) {
        printf("[PhSensor] - Wrong slave address");
        return;
    }
    bcm_init();
    addr = DEFAULT_ADDRESS | _addr;
    if (!deviceInfo()) {
        printf("Error reading pH Sensor");
        return;
    }
}

PhSensor::PhSensor(const PhSensor& orig) {
}

PhSensor::~PhSensor() {
}

bool PhSensor::deviceInfo() {
    wBuf[0] = 'i';
    selectModule();
    bcm2835_i2c_write(wBuf, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    bcm2835_i2c_read(rBuf, 20);
//    printf("Message: %s\n", rBuf);
    std::cout<<"[pHSensor] - deviceInfo: "<<std::string(rBuf)<<std::endl;
    if (rBuf[0] == 1) {
        return true;
    }
}

float PhSensor::reading() {
    wBuf[0] = 'R';
    selectModule();
    bcm2835_i2c_write(wBuf, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    bcm2835_i2c_read(rBuf, 20);
    std::string message = rBuf;
//    std::string::size_type sz;
//    printf("Full Message: %s\n", message);
//    std::cout<<"Full Message: "<<message<<std::endl;
//    printf("Message: %.3f\n", result);
    float result = -10;
    if (rBuf[0] != 0x01) {
        printf("[pH Sensor] -> Message Error\n");
        // std::this_thread::sleep_for(std::chrono::milliseconds(150));
        // bcm2835_i2c_read(rBuf, 20);
        return result;
    }
    try {
        result = std::stof(message.substr(1, 6));
    } catch (const std::exception& e) {
//        std::cout<<"[pH Sensor] - Error: "<<e.what()<<" => Last Message: "<<message<<std::endl;
        result = -10;
//        std::cout<<"[pH Sensor] - Last Message: "<<message<<std::endl;
    }
//    std::cout<<result;
    return result;
}

float PhSensor::roundedValue(float value) {
    float newValue = std::floor((value * 100) + .5) / 100;
    return newValue;
}

void PhSensor::tempCompensation(float temp) {
    std::snprintf(wBuf, 20, "T,%0.1f", temp);
    printf("Message: %s\n", wBuf);
    selectModule();
    bcm2835_i2c_write(wBuf, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    bcm2835_i2c_read(rBuf, 20);

    if (rBuf[0] != 1) {
        printf("[PhSensor] - Error setting temp compensation\n");
    }
}

void PhSensor::calibrate(uint8_t point, float phValue) {
    std::snprintf(wBuf, 20, "Cal,%s,%0.2f", calibrateString(point).c_str(), phValue);
    printf("Message: %s\n", wBuf);
    selectModule();
//    bcm2835_i2c_write(wBuf, 6);
//    std::this_thread::sleep_for(std::chrono::milliseconds(300));
//    bcm2835_i2c_read(rBuf, 20);
//
//    if (rBuf[0] != 1) {
//        printf("[PhSensor] - Error setting temp compensation\n");
//    }
}

std::string PhSensor::calibrateString(uint8_t point) {
    switch(point) {
        case MID_CALIBRATION:
            return "mid";
        case LOW_CALIBRATION:
            return "low";
        case HIGH_CALIBRATION:
            return "high";
    }
    return "";
}

void PhSensor::selectModule(){
    bcm2835_i2c_setSlaveAddress(addr);
}

void PhSensor::bcm_init(){
    // - 400kHz aproximadamente...
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500;
    // - La direccion del esclavo se establece en cada modulo

    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }

    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
}

void PhSensor::bcm_end(){
    bcm2835_i2c_end();
    bcm2835_close();
}
