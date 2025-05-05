#include "gestures.hpp"

#include "pinmap.hpp"

/*
 * Predefined gestures which we can trigger
 */ 

int gesture_nop(gesture_type_t* gesture, bool trigger, int state) {
    return -1;
}



const gesture_t GESTURE_DOUBLE_TAP = {
    .func = gesture_nop,
    .n_pins = 1,
    .pin = { TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_TAP_AND_HOLD = {
    .func = gesture_nop,
    .n_pins = 1,
    .pin = { TOUCH_X_PIN[0] }
};

// Toggle speak-to-chat
const gesture_t GESTURE_TWO_FINGER_LONG = {
    .func = gesture_nop,
    .n_pins = 2,
    .pin = { TOUCH_X_PIN[0], TOUCH_X_PIN[3] }
};

const gesture_t GESTURE_SWIPE_FWD = {
    .func = gesture_nop,
    .n_pins = 4,
    .pin = { TOUCH_X_PIN[0], TOUCH_X_PIN[1], TOUCH_X_PIN[2], TOUCH_X_PIN[3] }
};

const gesture_t GESTURE_SWIPE_BWD = {
    .func = gesture_nop,
    .n_pins = 4,
    .pin = { TOUCH_X_PIN[3], TOUCH_X_PIN[2], TOUCH_X_PIN[1], TOUCH_X_PIN[0] }
};

const gesture_t GESTURE_SWIPE_UP = {
    .func = gesture_nop,
    .n_pins = 4,
    .pin = { TOUCH_Y_PIN[0], TOUCH_Y_PIN[1], TOUCH_Y_PIN[2], TOUCH_Y_PIN[3] }
};

const gesture_t GESTURE_SWIPE_DOWN = {
    .func = gesture_nop,
    .n_pins = 4,
    .pin = { TOUCH_Y_PIN[3], TOUCH_Y_PIN[2], TOUCH_Y_PIN[1], TOUCH_Y_PIN[0] }
};

