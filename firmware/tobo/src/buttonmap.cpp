#include "buttonmap.hpp"
#include "gestures.hpp"

/*
 * This is where you control which
 * button performs what action!
 * 
 * Each button has exactly one gesture configured.
 * They are configured in order, with button 0 first in the array.
 * 
 * You can choose from any of the GESTURE_* macros defined in gestures.hpp
 * or implement your own if you want something really special.
 * 
 * Be aware, you can't just _remove_ an entry from this list.
 * If you want a button to do nothing, assign it GESTURE_NOP.
 */
const gesture_t* BTN_ACTION[N_BTNS] = {
    &GESTURE_SWIPE_BWD,         // Button 0, Reverse
    &GESTURE_SWIPE_UP,          // Button 1, Vol+
    &GESTURE_DOUBLE_TAP,        // Button 2, Play/Pause
    &GESTURE_SWIPE_DOWN,        // Button 3, Vol-
    &GESTURE_SWIPE_FWD,         // Button 4, Ffwd
    &GESTURE_TAP_AND_HOLD,      // Button 5, Voice assistant
    &GESTURE_PALM,              // Button 6, Hold to listen
    &GESTURE_TWO_FINGER_LONG    // Button 7, Toggle speak-to-chat
};
