#include "PhaseDriver.hpp"
#include "mbed_assert.h"
#include "cmsis.h"
#include "pinmap.h"

//  note: much of the code in here is copied from pwmout_api.c and gpio_api.c

static unsigned int pwm_clock_mhz;


//  PORT ID, PWM ID, Pin function
static const PinMap PinMap_PWM[] = {
    {P1_18, PWM_1, 2},
    {P1_20, PWM_2, 2},
    {P1_21, PWM_3, 2},
    {P1_23, PWM_4, 2},
    {P1_24, PWM_5, 2},
    {P1_26, PWM_6, 2},
    {P2_0 , PWM_1, 1},
    {P2_1 , PWM_2, 1},
    {P2_2 , PWM_3, 1},
    {P2_3 , PWM_4, 1},
    {P2_4 , PWM_5, 1},
    {P2_5 , PWM_6, 1},
    {P3_25, PWM_2, 3},
    {P3_26, PWM_3, 3},
    {NC, NC, 0}
};




/*
    //PWM code on channel 2 and 4 (LED2/4 on MBED)
    LPC_SC->PCONP|=(1<<6);                                                        //enable power on PWM1
    LPC_SC->PCLKSEL0|=(3<<12);                                                    //run PWM1 clock at prescaler 8 (96MHz/8 = 12MHz)
    LPC_PINCON->PINSEL3|=(2<<14) | (2<<8);                                        //PWM on channel 2 and 4
    LPC_PINCON->PINMODE3|=(2<<14) | (2<<8);                                       //no pull ups/pull downs on PIN1.20 and 1.23
    LPC_PWM1->MCR|=(0<<14) | (0<<13) | (0<<12) | (0<<8) | (0<<7) | (0<<6) | (1<<1);        //no interrupt, no reset, no stop of TC compare match
    LPC_PWM1->CTCR|=(0<<0);                                                       //timer mode
    LPC_PWM1->PCR|=(1<<12) | (1<<10) | (1<<4) | (1<<2);                           //double edge control on channel 2 and 4
    LPC_PWM1->PR=1199999;                                                         //pre scale PWM to 10 Hz
    LPC_PWM1->MR0=9;                                                              //top value of timer/counter, reset counter on match
    LPC_PWM1->MR1=2;                                                              //ON LED 2 after 2 counts
    LPC_PWM1->MR2=9;                                                              //OFF LED 2 after 9 counts
    LPC_PWM1->MR3=5;                                                              //ON LED 4 after 6 counts
    LPC_PWM1->MR4=8;                                                              //OFF LED 4 after 9 counts
    LPC_PWM1->LER|=(1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0);                    //update values
    LPC_PWM1->TCR|=(1<<3) | (1<<0);                                               //enable PWM and timer NOW
*/




PhaseDriver::PhaseDriver(PinName highPin, PinName lowPin, int bufferTimeUs);
    _highPin(highPin), _lowPin(lowPin), _bufferTimeUs(bufferTimeUs)
{
    _value = 0; //  start in pwm mode w/duty cycle 0

    PWMName pwmHigh = (PWMName)pinmap_peripheral(highPin, PinMap_PWM);
    PWMName pwmLow = (PWMName)pinmap_peripheral(lowPin, PinMap_PWM);
    MBED_ASSERT(pwmHigh != (PWMName)NC && pwmLow != (PWMName)NC);

    //  ensure the power is on
    LPC_SC->PCONP |= 1 << 6;

    //  ensure clock to /4
    LPC_SC->PCLKSEL0 &= ~(0x3 << 12);   //  pclk = /4
    LPC_PWM1->PR = 0;                   //  no prescale

    //  ensure single PWM mode
    LPC_PWM1->MCR = 1 << 1; //  reset TC on match 0

    //  turn on double edge control for both pins
    LPC_PWM1->PCR |= (1 << (8 + pwmHigh)) | (1 << pwmHigh);
    LPC_PWM1->PCR |= (1 << (8 + pwmLow)) | (1 << pwmLow);

    pwm_clock_mhz = SystemCoreClock / 4000000;


//////  set period to 20ms = 20000us
    uint32_t ticks = pwm_clock_mhz * 20000;

    //  set reset
    LPC_PWM1->TCR = TCR_RESET;

    //  set the global match register
    LPC_PWM1->MR0 = ticks;

    //  set the channel latch to update value at next period start
    LPC_PWM1->LER |= 1 << 0;

    //  enable counter and pwm, clear reset
    LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;
}

void PhaseDriver::write(float value) {
    if (value == _value) return;

    if (value == -1) {

        //  FIXME: set it to ground

    } else {
        if (value < 0) value = 0;
        else if (value > 1) value = 1;

        //  FIXME: switch to pwm mode if needed, set duty cycles
    }
}

// void switchToDigitalIoMode(PinName pin, int value) {
//     gpio_t gpio;
//     gpio_init_out_ex(&gpio, pin, int value);  //  see gpio.c
// }
