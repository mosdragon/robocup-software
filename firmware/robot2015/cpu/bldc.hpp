#pragma once


class BLDC {
public:
    BLDC(PinName h0, PinName h1, PinName h2,
        PinName p0h, PinName p1h, PinName p2h,
        PinName p0l, PinName p1l, PinName p2l) :
            _hall0(h0), _hall1(h1), _hall2(h2),
            _phase0h(p0h), _phase1h(p1h), _phase2h(p2h),
            _phase0l(p0l), _phase1l(p1l), _phase2l(p2l),
            _dutyCycle(0), _forward(true), _hallFault(false)
    {

    }


    void setDutyCycle(float dutyCycle) {
        _dutyCycle = dutyCycle;
        if (_dutyCycle > 1) {
            _dutyCycle = 1;
        } else if (dutyCycle < 0) {
            _dutyCycle = 0;
        }
    }

    float dutyCycle() const {
        return _dutyCycle;
    }

    void setForward(bool forward = true) {
        _forward = forward;
    }

    bool isForward() const {
        return _forward;
    }

    void stop() {
        setDutyCycle(0);
        update();
    }

    void update() {
        int hallValue = (_hall2.read() << 2) | (_hall1.read() << 1) | (_hall0.read());

        //  check for hall faults
        //  000 and 111 are invalid hall codes
        _hallFault = (hallValue == 0b111) || (hallValue == 0b000);
        if (_hallFault) std::cout << "Encountered a hall fault!" << std::endl;


    }


    bool hasHallFault() const {
        return _hallFault;
    }


private:
    float _dutyCycle;
    bool _forward;

    bool _hallFault;

    DigitalIn _hall0;
    DigitalIn _hall1;
    DigitalIn _hall2;

    PwmOut _phase0h;
    PwmOut _phase1h;
    PwmOut _phase2h;

    PwmOut _phase0l;
    PwmOut _phase1l;
    PwmOut _phase2l;   
};



