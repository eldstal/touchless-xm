#pragma once

typedef enum _gesture_type : unsigned char {
    tap_and_hold = 0,
    double_tap = 1,
    swipe_repeat = 2,
    swipe_and_hold = 3,
    long_press = 4
} gesture_type_t;

// A state machine implementing a gesture
// Returns -1 when the gesture is completed
typedef int (*gesture_func_t)(gesture_type_t* gesture, bool trigger, int state);

typedef struct {
    gesture_func_t func;
    unsigned char n_pins;
    unsigned char pin[4];
} gesture_t;

/*
 * Predefined gestures which we can trigger
 */ 

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
