#pragma once

#include <cmath>

//http://www.maxonmotorusa.com/medias/sys_master/8798093541406/EC-Technik-kurz-und-buendig-11-EN-026-027.pdf?attachment=true
//Document contains relation from Hall State to Phase Voltages

DigitalOut h1ind(LED1);
DigitalOut h2ind(LED2);
DigitalOut h3ind(LED3);


typedef struct {
    int phase1;
    int phase2;
    int phase3;
    //0 is high impedance (high Z)
    //-1 is ground
    //1 is duty cycle
} DriverState;

static const DriverState DriverStates[8] = {
    { 0, 0, 0}, //fail state, all phases high-Z
    { 1, 0,-1},
    {-1, 1, 0},
    { 0, 1,-1},
    { 0,-1, 1},
    { 1,-1, 0},
    {-1, 0, 1},
    { 0, 0, 0} //fail state, all phases high-Z
};

class BLDC {
public:
    BLDC(PinName h1, PinName h2, PinName h3, PinName p1h, PinName p2h, PinName p3h) :
            _power(0.5), _hallFault(false),
            _hall1(h1), _hall2(h2), _hall3(h3),
            _phase1h(p1h), _phase2h(p2h), _phase3h(p3h)
    {
        //  note: setting the period of one pwm sets them all since they share the same global period value
        _phase1h.period_us(50);
    }

    void update() {
        int hallValue = (_hall3.read() << 2) | (_hall2.read() << 1) | (_hall1.read());

        // printf("hall: %d%d%d - ", _hall3.read(), _hall2.read(), _hall1.read());

        //  check for hall faults
        //  000 and 111 are invalid hall codes
        _hallFault = (hallValue == 0b111) || (hallValue == 0b000);
        // if (_hallFault) std::cout << "Encountered a hall fault!" << std::endl;

        DriverState state = DriverStates[hallValue];

        //  negate phases for backwards drive
        if (_power < 0) {
            state.phase1 *= -1;
            state.phase2 *= -1;
            state.phase3 *= -1;
        }


        PwmOut outs[] = {
            _phase1h,
            _phase2h,
            _phase3h
        };

        float newValues[] = {
            ((state.phase1 == 1) ? 1 : 0) * abs(_power),
            ((state.phase2 == 1) ? 1 : 0) * abs(_power),
            ((state.phase3 == 1) ? 1 : 0) * abs(_power),
        };

        for (int i = 0; i < 3; i++) {
            outs[i].write(newValues[i]);
        }

        h1ind = outs[0] > 0 ? 1 : 0;
        h2ind = outs[1] > 0 ? 1 : 0;
        h3ind = outs[2] > 0 ? 1 : 0;

        // printf("high: %.2f-%.2f-%.2f\r\n", _phase1h.read(), _phase2h.read(), _phase3h.read());
    }


    //  can be + or - for forwards and backwards.  Ranges from zero to one
    void setPower(float power) {
        if (abs(power) > 1) power = signbit(power) * 1.0; //  limit to [-1, 1]
        _power = power;
    }

    void operator=(float power0) {
        setPower(power0);
    }


    bool hasHallFault() const {
        return _hallFault;
    }


private:
    float _power;

    bool _hallFault;

    DigitalIn _hall1;
    DigitalIn _hall2;
    DigitalIn _hall3;

    PwmOut _phase1h;
    PwmOut _phase2h;
    PwmOut _phase3h;
};
