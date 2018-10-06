
#include "hexapod.h"
#include "servo.h"
#include "debug.h"

// TBD: move to hal
#include <LFlash.h>

namespace hexapod {

    HexapodClass Hexapod;

    HexapodClass::HexapodClass(): 
        legs_{{0}, {1}, {2}, {3}, {4}, {5}}, 
        movement_{MOVEMENT_STANDBY},
        mode_{MOVEMENT_STANDBY}
    {

    }

    void HexapodClass::init(bool setting) {
        Servo::init();

        LFlash.begin();
        calibrationLoad();

        // default to standby mode
        if (!setting)
            processMovement(MOVEMENT_STANDBY);

        LOG_INFO("Hexapod init done.");
    }

    void HexapodClass::processMovement(MovementMode mode, int elapsed) {
        if (mode_ != mode) {
            mode_ = mode;
            movement_.setMode(mode_);
        }

        auto& location = movement_.next(elapsed);
        for(int i=0;i<6;i++) {
            legs_[i].moveTip(location.get(i));
        }
    }

    void HexapodClass::calibrationSave() {

        short data[6*3*2];

        for(int i=0;i<6;i++) {
            for(int j=0;j<3;j++) {
                int offset, scale;
                legs_[i].get(j)->getParameter(offset, scale);
                data[2*3*i + 2*j] = (short)offset;
                data[2*3*i + 2*j + 1] = (short)scale;
            }
        }

        LFlash.write(
            "HEXAPOD",
            "CALI",
            LFLASH_RAW_DATA,
            (const uint8_t *)data,
            sizeof(data)
        );

    }

    void HexapodClass::calibrationGet(int legIndex, int partIndex, int& offset, int& scale) {
        legs_[legIndex].get(partIndex)->getParameter(offset, scale);
    }

    void HexapodClass::calibrationSet(int legIndex, int partIndex, int offset, int scale) {
        legs_[legIndex].get(partIndex)->setParameter(offset, scale);
    }

    void HexapodClass::calibrationTest(int legIndex, int partIndex, float angle) {
        legs_[legIndex].get(partIndex)->setAngle(angle);
    }

    void HexapodClass::calibrationLoad() {
        short data[6*3*2] = {0};
        uint32_t size = sizeof(data);

        LFlash.read(
            "HEXAPOD",
            "CALI",
            (uint8_t *)data,
            &size
        );

        for(int i=0;i<6;i++) {
            for(int j=0;j<3;j++) {
                legs_[i].get(j)->setParameter(data[2*3*i + 2*j], data[2*3*i + 2*j + 1], false);
            }
        }
    }

}