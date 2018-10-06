#pragma once

namespace hexapod { 

    class Servo {
    public:
        static void init(void);

    public:
        Servo(int legIndex, int partIndex);

        // angle: 0 means center, range is -60~60
        void setAngle(float angle);
        float getAngle(void);

        void getParameter(int& offset, int& scale) {
            offset = offset_;
            scale = scale_;
        }

        void setParameter(int offset, int scale, bool update = true) {
            offset_ = offset;
            scale_ = scale;
            if (update)
                setAngle(angle_);
        }

    private:
        float angle_;
        int pwmIndex_;
        bool inverse_;
        int offset_;
        int scale_;
        int range_;
        float adjust_angle_;
    };

}