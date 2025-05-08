#include <Arduino.h>

#include <LowPower.h>
#include <PinChangeInterrupt.h>
#include <SimplyAtomic.h>

#include "pinmap.hpp"
#include "gestures.hpp"
#include "debounce.hpp"
#include "buttonmap.hpp"

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



void setup_pins() {
    for (unsigned char p=0; p<N_BTNS; ++p) {
        pinMode(BTN_PIN[p], INPUT_PULLUP);
    }

    for (unsigned char p=0; p<N_TOUCH_X; ++p) {
        pinMode(TOUCH_X_PIN[p], OUTPUT);
        digitalWrite(TOUCH_X_PIN[p], TOUCH_INACTIVE);
    }

    for (unsigned char p=0; p<N_TOUCH_Y; ++p) {
        pinMode(TOUCH_Y_PIN[p], OUTPUT);
        digitalWrite(TOUCH_Y_PIN[p], TOUCH_INACTIVE);
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

    bool any_triggered = true;

    // Handle any queued up interrupts
    while (any_triggered) {
        
        // Allow buttons to settle
        delay(DEBOUNCE_MS);
        long now = millis();

        any_triggered = false;

        for (uint8_t p=0; p<N_BTNS; p++) {
            
            bool pin_triggered = false;
            ATOMIC() {
                pin_triggered = debounced_check(&debounce[p], now, BUTTON_ACTIVE);
            }

            if (!pin_triggered) continue;

            any_triggered = true;

            gesture_perform(BTN_ACTION[p], BTN_PIN[0]); 

        }
    }

    //delay(1000);
}
