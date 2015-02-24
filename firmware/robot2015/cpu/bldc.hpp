#pragma once

//http://www.maxonmotorusa.com/medias/sys_master/8798093541406/EC-Technik-kurz-und-buendig-11-EN-026-027.pdf?attachment=true
//Document contains relation from Hall State to Phase Voltages
class BLDC {
public:
    BLDC(PinName h1, PinName h2, PinName h3,
        PinName p1h, PinName p2h, PinName p3h,
        PinName p1l, PinName p2l, PinName p3l) :
            _hall1(h1), _hall2(h2), _hall3(h3),
            _phase1h(p1h), _phase2h(p2h), _phase3h(p3h),
            _phase1l(p1l), _phase2l(p2l), _phase3l(p3l),
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
        int hallValue = (_hall3.read() << 2) | (_hall2.read() << 1) | (_hall1.read());

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

    DigitalIn _hall1;
    DigitalIn _hall2;
    DigitalIn _hall3;

    PwmOut _phase1h;
    PwmOut _phase2h;
    PwmOut _phase2h;

    PwmOut _phase1l;
    PwmOut _phase2l;
    PwmOut _phase3l;   
};



