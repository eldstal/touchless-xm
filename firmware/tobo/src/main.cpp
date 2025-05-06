#include <Arduino.h>

#include <LowPower.h>
#include <PinChangeInterrupt.h>

#include "pinmap.hpp"
#include "gestures.hpp"



void btn_interrupt() {
}

void setup_pins() {
    for (unsigned char p=0; p<N_BTNS; ++p) {
        pinMode(BTN_PIN[p], INPUT_PULLUP);
    }

    for (unsigned char p=0; p<N_TOUCH_X; ++p) {
        pinMode(TOUCH_X_PIN[p], OUTPUT);
    }

    for (unsigned char p=0; p<N_TOUCH_Y; ++p) {
        pinMode(TOUCH_Y_PIN[p], OUTPUT);
    }
}



void setup_interrupts() {
    attachPCINT(digitalPinToPCINT(BTN_PIN[0]), btn_interrupt, CHANGE);
}

void setup()
{
    setup_pins();
    setup_interrupts();

}

void loop()
{

    // Sleep until an interrupt
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    gesture_perform(&GESTURE_SWIPE_BWD, BTN_PIN[0]);
    //delay(1000);
}
