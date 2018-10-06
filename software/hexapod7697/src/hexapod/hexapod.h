#pragma once

#include "movement.h"
#include "leg.h"

namespace hexapod {

    class HexapodClass {
    public:
        HexapodClass();

        // init

        void init(bool setting = false);

        // Movement API

        void processMovement(MovementMode mode, int elapsed = 0);

        // Calibration API

        void calibrationSave(); // write to flash
        void calibrationGet(int legIndex, int partIndex, int& offset, int& scale);  // read servo setting
        void calibrationSet(int legIndex, int partIndex, int offset, int scale);    // update servo setting
        void calibrationTest(int legIndex, int partIndex, float angle);             // test servo setting

    private:
        void calibrationLoad(); // read from flash

    private:
        MovementMode mode_;
        Movement movement_;
        Leg legs_[6];
    };

    extern HexapodClass Hexapod;
}