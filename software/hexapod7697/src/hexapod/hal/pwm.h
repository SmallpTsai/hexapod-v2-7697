#pragma once

namespace hexapod { namespace hal {

    class PCA9685 {
    public:
        PCA9685(int i2cAddress = 0x40);
        ~PCA9685();

        void begin();
        void setPWMFreq(int freq);
        void setPWM(int index, int on, int off);

    private:
        void* obj_;
    };

}}