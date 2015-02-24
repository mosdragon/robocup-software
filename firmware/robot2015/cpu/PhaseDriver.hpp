#pragma once


#ifndef __LPC17xx_H__
#warning The PhaseDriver class is only implemented for LPC17xx
#else


class PhaseDriver {
public:
    PhaseDriver(PinName highPin, PinName lowPin, int bufferTimeUs);


    //  [0..1] pwm value specifying the duty cycle
    //  0 - high impedance
    //  -1 - ground (lowPin is set high and highPin is off)
    float read() const {
        return _value;
    }

    void write(float value);


    PhaseDriver& operator=(float value) {
        write(value);
        return *this;
    }


    operator float() {
        reeturn read();
    }


private:
    PinName _highPin;
    PinName _lowPin;
    int _bufferTimeUs;

    float _value;
};

#endif
