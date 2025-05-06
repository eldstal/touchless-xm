#pragma once

#include <stdint.h>


struct gesture;
typedef struct gesture gesture_t;

// A state machine implementing a gesture
// Returns -1 when the gesture is completed
typedef int16_t (*gesture_func_t)(const gesture_t* gesture, bool trigger, int16_t state);

struct gesture {
    gesture_func_t func;
    uint8_t n_pins;
    uint8_t pin[4];
};



/*
 * Perform a gesture
 */
extern void gesture_perform(const gesture_t* gesture, uint8_t trigger_pin);

/*
 * Predefined gestures which we can trigger
 */ 

// Do nothing
extern const gesture_t GESTURE_NOP;

// Nothing, probably
extern const gesture_t GESTURE_TAP;

// Play/pause
extern const gesture_t GESTURE_DOUBLE_TAP;

// Voice assistant
extern const gesture_t GESTURE_TAP_AND_HOLD;

// Toggle speak-to-chat
extern const gesture_t GESTURE_TWO_FINGER_LONG;

// FFWD
extern const gesture_t GESTURE_SWIPE_FWD;

// REV
extern const gesture_t GESTURE_SWIPE_BWD;

// Volume up
extern const gesture_t GESTURE_SWIPE_UP;

// Volume down
extern const gesture_t GESTURE_SWIPE_DOWN;
