#pragma once

#include "pinmap.h"

typedef enum _gesture_type : unsigned char {
    tap_and_hold = 0,
    double_tap = 1,
    swipe = 2,
    swipe_and_hold = 3
} gesture_type_t;

typedef struct {
    gesture_type_t type;

    unsigned char n_pins;
    unsigned char pin[4];
} gesture_t;


const gesture_t GESTURE_DOUBLE_TAP = {
    .type = double_tap
};