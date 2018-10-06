
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "pwm.h"

namespace hexapod { namespace hal {

    PCA9685::PCA9685(int i2cAddress) {
        obj_ = (void*)new Adafruit_PWMServoDriver(i2cAddress);
    }

    PCA9685::~PCA9685() {
        delete ((Adafruit_PWMServoDriver*)obj_);
    }

    void PCA9685::begin() {
        ((Adafruit_PWMServoDriver*)obj_)->begin();
    }

    void PCA9685::setPWMFreq(int freq) {
        ((Adafruit_PWMServoDriver*)obj_)->setPWMFreq(freq);
    }

    void PCA9685::setPWM(int index, int on, int off) {
        ((Adafruit_PWMServoDriver*)obj_)->setPWM(index, (uint16_t)on, (uint16_t)off);
    }

}}