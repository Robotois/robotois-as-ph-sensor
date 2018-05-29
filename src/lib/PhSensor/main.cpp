/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: yovany
 *
 * Created on May 25, 2018, 10:34 AM
 */

#include <cstdlib>
#include "PhSensor.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
    PhSensor phSensor;
    phSensor.calibrate(MID_CALIBRATION, 7.15);
//    phSensor.tempCompensation(20.3);
//    float reading = phSensor.reading();
//    printf("Message: %.2f\n", reading);
    return 0;
}
