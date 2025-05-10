#include <Arduino.h>
#include <stdint.h>

#include "gestures.hpp"
#include "pinmap.hpp"

void gesture_perform(const gesture_t* gesture, uint8_t trigger_pin) {

    int16_t state = 0;
    
    while (true) {

        bool trigger_state = digitalRead(trigger_pin) == BUTTON_ACTIVE;

        state = gesture->func(gesture, trigger_state, state);

        if (state < 0) break;

    }
}



static int16_t gesture_nop(const gesture_t* gesture, bool trigger, int16_t state) {
    return -1;
}


static int16_t gesture_tap(const gesture_t* gesture, bool trigger, int16_t state) {
    switch (state) {
        case 0:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_ACTIVE);
                }
                delay(MS_TAP_DOWN);
                return 1;
            }
        
        case 1:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
                }
                return -1;
            }
    }

    return -1;
}


static int16_t gesture_tap_long(const gesture_t* gesture, bool trigger, int16_t state) {
    switch (state) {
        case 0:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_ACTIVE);
                }
                delay(MS_TAP_LONG);
                return 1;
            }
        
        case 1:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
                }
                return -1;
            }
    }

    return -1;
}

static int16_t gesture_double_tap(const gesture_t* gesture, bool trigger, int16_t state) {
    switch (state) {
        case 0:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_ACTIVE);
                }
                delay(MS_TAP_DOWN);
                return 1;
            }
        
        case 1:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
                }
                delay(MS_TAP_UP);
                return 2;
            }
        case 2:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_ACTIVE);
                }
                delay(MS_TAP_DOWN);
                return 3;
            }
        
        case 3:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
                }
                return -1;
            }
    }

    return -1;
}



static int16_t gesture_hold(const gesture_t* gesture, bool trigger, int16_t state) {
    switch (state) {
        case 0:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_ACTIVE);
                }
                delay(MS_TAP_DOWN);
                return 1;
            }

        case 1:
            {
                if (trigger) {
                    delay(MS_HOLD_CHECK);
                    return 1;
                } else {
                    return 2;
                }
            }
        
        case 2:
            {
                for (uint8_t i=0; i<gesture->n_pins; ++i) {
                    digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
                }
                return -1;
            }
    }

    return -1;
}

static int16_t gesture_swipe_and_repeat(const gesture_t* gesture, bool trigger, int16_t state) {
    const int16_t done_state = gesture->n_pins;
    const int16_t loop_state = done_state + 1;

    if (state < done_state) {
        digitalWrite(gesture->pin[state], TOUCH_ACTIVE);

        // The time while two points are active
        delay(MS_SWIPE_OVERLAP);

        if (state > 0) {
            digitalWrite(gesture->pin[state-1], TOUCH_INACTIVE);
        }

        // The time while this point is active on its own
        delay(MS_SWIPE_PASS);
        return state + 1;
    } else if (state == done_state) {

        for (uint8_t i=0; i<gesture->n_pins; ++i) {
            digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
        }

        delay(MS_SWIPE_REPEAT);
        return loop_state;
    
    } else if (state == loop_state) {

        if (trigger) {
            // Go again!
            return 0;

        } else {

            // Done!
            return -1;
        }
    }

    return -1;
}


static int16_t gesture_swipe_and_hold(const gesture_t* gesture, bool trigger, int16_t state) {
    int16_t hold_state = gesture->n_pins;

    if (state < hold_state) {
        digitalWrite(gesture->pin[state], TOUCH_ACTIVE);

        // Overlap
        delay(MS_SWIPE_OVERLAP);

        if (state > 0) {
            digitalWrite(gesture->pin[state-1], TOUCH_INACTIVE);
        }
        delay(MS_SWIPE_PASS);
        return state + 1;
    
    } else if (state == hold_state) {

        if (trigger) {
            // Just hold the "finger"
            delay(MS_HOLD_CHECK);
            return hold_state;
        } else {

            return hold_state + 1;
        }

    } else {

        for (uint8_t i=0; i<gesture->n_pins; ++i) {
            digitalWrite(gesture->pin[i], TOUCH_INACTIVE);
        }

        // Done!
        return -1;

    }

    return -1;
}


const gesture_t GESTURE_NOP = {
    .func = gesture_nop,
    .n_pins = 0,
    .pin = {  }
};

const gesture_t GESTURE_TAP = {
    .func = gesture_tap,
    .n_pins = 1,
    .pin = { TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_DOUBLE_TAP = {
    .func = gesture_double_tap,
    .n_pins = 1,
    .pin = { TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_TAP_AND_HOLD = {
    .func = gesture_hold,
    .n_pins = 1,
    .pin = { TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_PALM = {
    .func = gesture_hold,
    .n_pins = 4,
    .pin = { TOUCH_X_PIN[0], TOUCH_X_PIN[2], TOUCH_Y_PIN[1], TOUCH_Y_PIN[3] }
};

const gesture_t GESTURE_TWO_FINGER_LONG = {
    .func = gesture_tap_long,
    .n_pins = 2,
    .pin = { TOUCH_X_PIN[0], TOUCH_X_PIN[2] }
};

const gesture_t GESTURE_SWIPE_FWD = {
    .func = gesture_swipe_and_repeat,
    .n_pins = 3,
    .pin = { TOUCH_X_PIN[0], TOUCH_X_PIN[1], TOUCH_X_PIN[2] }
};

const gesture_t GESTURE_SWIPE_BWD = {
    .func = gesture_swipe_and_repeat,
    .n_pins = 3,
    .pin = { TOUCH_X_PIN[2], TOUCH_X_PIN[1], TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_SWIPE_UP = {
    .func = gesture_swipe_and_hold,
    .n_pins = 3,
    .pin = { TOUCH_Y_PIN[0], TOUCH_Y_PIN[1], TOUCH_Y_PIN[2] }
};

const gesture_t GESTURE_SWIPE_DOWN = {
    .func = gesture_swipe_and_hold,
    .n_pins = 3,
    .pin = { TOUCH_Y_PIN[2], TOUCH_Y_PIN[1], TOUCH_Y_PIN[0] }
};

