#include <Arduino.h>

#include <LowPower.h>
#include <PinChangeInterrupt.h>
#include <SimplyAtomic.h>

#include "pinmap.hpp"
#include "gestures.hpp"
#include "debounce.hpp"

int QUEUED_BTN = -1;



pin_debounce debounce[N_BTNS] = { };

#define GENERIC_BUTTON_INTERRUPT(idx) \
void btn_int_##idx() { \
    debounce_interrupt(&debounce[idx]); \
}


GENERIC_BUTTON_INTERRUPT(0)
GENERIC_BUTTON_INTERRUPT(1)
GENERIC_BUTTON_INTERRUPT(2)
GENERIC_BUTTON_INTERRUPT(3)
GENERIC_BUTTON_INTERRUPT(4)
GENERIC_BUTTON_INTERRUPT(5)
GENERIC_BUTTON_INTERRUPT(6)
GENERIC_BUTTON_INTERRUPT(7)


void btn_interrupt() {
    QUEUED_BTN = -1;
    for (unsigned char p=0; p<N_BTNS; ++p) {
        if (digitalRead(BTN_PIN[p]) == BUTTON_ACTIVE) {
            QUEUED_BTN = p;
        }
    }
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
    for (unsigned char p=0; p<N_BTNS; ++p) {
        debounce[p] = { .pin = BTN_PIN[p], .fresh = true };
    }

    attachPCINT(digitalPinToPCINT(BTN_PIN[0]), btn_int_0, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[1]), btn_int_1, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[2]), btn_int_2, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[3]), btn_int_3, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[4]), btn_int_4, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[5]), btn_int_5, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[6]), btn_int_6, CHANGE);
    attachPCINT(digitalPinToPCINT(BTN_PIN[7]), btn_int_6, CHANGE);
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

    // Allow buttons to settle
    delay(DEBOUNCE_MS);

    long now = millis();

    for (uint8_t p=0; p<N_BTNS; p++) {
        
        bool pin_triggered = false;
        ATOMIC() {
            pin_triggered = debounced_check(&debounce[p], now, BUTTON_ACTIVE);
        }

        if (!pin_triggered) continue;

        if (p == 0) {
            gesture_perform(&GESTURE_SWIPE_BWD, BTN_PIN[0]);
        } else {
            gesture_perform(&GESTURE_SWIPE_FWD, BTN_PIN[1]);
        } 

    }

    //delay(1000);
}
