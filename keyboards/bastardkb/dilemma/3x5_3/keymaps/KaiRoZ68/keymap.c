/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE
};

enum tap_dance_codes {
    DANCE_1,
    DANCE_2,
    DANCE_3,
    DANCE_4,
    DANCE_5,
    DANCE_X,
    DANCE_C,
    DANCE_V,
    DANCE_Y,
};

#define LOWER MO(_LOWER)
#define RAISE LT(_RAISE,KC_BSPC)
#define ADJU MO(_ADJUST)
#define EMS LT(_MOUSE,KC_E)
#define WBSPC LCTL(KC_BSPC)

/*Combos*/
enum combos {
  QW_ESC,
  AS_TAB
};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM as_combo[] = {KC_A, LALT_T(KC_S), COMBO_END};

combo_t key_combos[] = {
  [QW_ESC] = COMBO(qw_combo, KC_ESC),
  [AS_TAB] = COMBO(as_combo, KC_TAB),
};


/*drag scroll*/
enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 64.0
#define SCROLL_DIVISOR_V 64.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
/*layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
        set_scrolling = false;
    }
    return state;
}
*/



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,            KC_W,           EMS,           KC_R,          KC_T,       TD(DANCE_Y),    KC_U,           KC_I,           KC_O,          KC_P,
    KC_A,            LALT_T(KC_S),   LCTL_T(KC_D),   LGUI_T(KC_F),  KC_G,       KC_H,   RGUI_T(KC_J),   RCTL_T(KC_K),   RALT_T(KC_L),  KC_SCLN,
    LSFT_T(KC_Z),    TD(DANCE_X),    TD(DANCE_C),    TD(DANCE_V),   KC_B,       KC_N,           KC_M,           KC_COMM,        KC_DOT,        RSFT_T(KC_SLSH),
                              ADJU,        LOWER,         KC_ENTER,   KC_SPC,         RAISE,             KC_DEL
    ),

/* Lower */
[_LOWER] = LAYOUT_split_3x5_3(
LSFT(KC_1),      LSFT(KC_2),    LSFT(KC_3), LSFT(KC_4),     LSFT(KC_5), LSFT(KC_6),     LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0),
RALT(KC_8),      KC_NUBS,       RALT(KC_7), RALT(KC_NUBS),  _______,    LSFT(KC_RBRC),  KC_MINUS,   KC_QUOTE,   KC_LBRC,    LSFT(KC_MINUS),
RALT(KC_9),      LSFT(KC_NUBS), RALT(KC_0), RALT(KC_MINS),  _______,    LSFT(KC_BSLS),  KC_EQUAL,   KC_RBRC,    KC_BSLS,    _______,
                                _______,    _______ ,       _______,    _______,        LCTL(KC_BSPC),    _______
),

/* Raise */

[_RAISE] = LAYOUT_split_3x5_3(
    TD(DANCE_1),   TD(DANCE_2),    TD(DANCE_3),    TD(DANCE_4),    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
    KC_F11,        KC_F12,         KC_PGUP,        KC_PGDN,        KC_HOME,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_END,
    KC_F1,         KC_F2,          KC_F3,          KC_F4,          KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,
                                   KC_ESC,        _______,        _______,  _______,  _______,  _______
),


[_ADJUST] = LAYOUT_split_3x5_3(
    QK_BOOT,    DT_PRNT, KC_VOLU, _______, KC_Z,     RGB_TOG,        RGB_MOD, RGB_HUI,  RGB_SAI, RGB_VAI,
    _______,    DT_UP, KC_VOLD, _______, _______,     _______,        RGB_RMOD, RGB_HUD,  RGB_SAD, RGB_VAD,
    QK_BOOTLOADER,   DT_DOWN, KC_MUTE, _______, _______, _______,       _______, _______,  _______, QK_BOOTLOADER,
                            _______, _______, _______, _______,         _______,  _______
),


[_MOUSE] = LAYOUT_split_3x5_3(
    QK_BOOT,    DB_TOGG, _______, DRAG_SCROLL, _______,    RGB_TOG,        RGB_MOD, RGB_HUI,  RGB_SAI, RGB_VAI,
    _______,    _______, _______, _______, CG_TOGG,     _______,        _______, RGB_HUD,  RGB_SAD, RGB_VAD,
    _______,    _______, _______, _______, _______, _______,       _______, _______,  _______, QK_BOOTLOADER,
                                     KC_BTN3, KC_BTN2, KC_BTN1,         _______,         _______,  _______
)
};


// clang-format on
/*
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
*/

/*Hold_on_other_key_press_per_key*/
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_Z):
            // Immediately select the hold action when another key is pressed.
            return true;
        case RSFT_T(KC_SLSH):
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}


/*TapDance Code=============================================================================*/

extern bool g_suspend_state;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

/*DANCE_1================================================================================*/

void on_dance_1(tap_dance_state_t *state, void *user_data);
uint8_t dance_1_dance_step(tap_dance_state_t *state);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_1);
		tap_code16(KC_1);
		tap_code16(KC_1);
	}
	if(state->count > 3) {
		tap_code16(KC_1);
	}
}

uint8_t dance_1_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_1_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_1_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_1); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_1)); break;
		case DOUBLE_TAP: register_code16(KC_1); register_code16(KC_1); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_1); register_code16(KC_1);
	}
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_1); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_1)); break;
		case DOUBLE_TAP: unregister_code16(KC_1); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_1); break;

	dance_state.step = 0;
    }
}

/*DANCE_2=====================================================================================*/

void on_dance_2(tap_dance_state_t *state, void *user_data);
uint8_t dance_2_dance_step(tap_dance_state_t *state);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_2);
		tap_code16(KC_2);
		tap_code16(KC_2);
	}
	if(state->count > 3) {
		tap_code16(KC_2);
	}
}

uint8_t dance_2_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_2_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_2_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_2); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_2)); break;
		case DOUBLE_TAP: register_code16(KC_2); register_code16(KC_2); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_2); register_code16(KC_2);
	}
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_2); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_2)); break;
		case DOUBLE_TAP: unregister_code16(KC_2); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_2); break;

	dance_state.step = 0;
    }
}

/*DANCE_3=====================================================================================*/

void on_dance_3(tap_dance_state_t *state, void *user_data);
uint8_t dance_3_dance_step(tap_dance_state_t *state);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_3);
		tap_code16(KC_3);
		tap_code16(KC_3);
	}
	if(state->count > 3) {
		tap_code16(KC_3);
	}
}

uint8_t dance_3_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_3_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_3_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_3); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_3)); break;
		case DOUBLE_TAP: register_code16(KC_3); register_code16(KC_3); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
	}
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_3); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_3)); break;
		case DOUBLE_TAP: unregister_code16(KC_3); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;

	dance_state.step = 0;
    }
}


/*DANCE_4 ====================================================================================*/

void on_dance_4(tap_dance_state_t *state, void *user_data);
uint8_t dance_4_dance_step(tap_dance_state_t *state);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_4);
		tap_code16(KC_4);
		tap_code16(KC_4);
	}
	if(state->count > 3) {
		tap_code16(KC_4);
	}
}

uint8_t dance_4_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_4_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_4_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_4); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_4)); break;
		case DOUBLE_TAP: register_code16(KC_4); register_code16(KC_4); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4);
	}
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_4); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_4)); break;
		case DOUBLE_TAP: unregister_code16(KC_4); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;

	dance_state.step = 0;
    }
}

/*DANCE_5===============================================================================*/

void on_dance_5(tap_dance_state_t *state, void *user_data);
uint8_t dance_5_dance_step(tap_dance_state_t *state);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_BSPC);
		tap_code16(KC_BSPC);
		tap_code16(KC_BSPC);
	}
	if(state->count > 3) {
		tap_code16(KC_BSPC);
	}
}

uint8_t dance_5_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_5_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_5_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_BSPC); break;
		case SINGLE_HOLD: register_code16(WBSPC); break;
		case DOUBLE_TAP: register_code16(KC_BSPC); register_code16(KC_BSPC); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_BSPC); register_code16(KC_BSPC);
	}
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_BSPC); break;
		case SINGLE_HOLD: unregister_code16(WBSPC); break;
		case DOUBLE_TAP: unregister_code16(KC_BSPC); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSPC); break;

	dance_state.step = 0;
    }
}

/*DANCE_X===============================================================================*/

void on_dance_X(tap_dance_state_t *state, void *user_data);
uint8_t dance_X_dance_step(tap_dance_state_t *state);
void dance_X_finished(tap_dance_state_t *state, void *user_data);
void dance_X_reset(tap_dance_state_t *state, void *user_data);

void on_dance_X(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_X);
		tap_code16(KC_X);
		tap_code16(KC_X);
	}
	if(state->count > 3) {
		tap_code16(KC_X);
	}
}

uint8_t dance_X_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_X_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_X_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_X); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_X)); break;
		case DOUBLE_TAP: register_code16(KC_X); register_code16(KC_X); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_X); register_code16(KC_X);
	}
}

void dance_X_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_X); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_X)); break;
		case DOUBLE_TAP: unregister_code16(KC_X); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_X); break;

	dance_state.step = 0;
    }
}

/*DANCE_C===============================================================================*/

void on_dance_C(tap_dance_state_t *state, void *user_data);
uint8_t dance_C_dance_step(tap_dance_state_t *state);
void dance_C_finished(tap_dance_state_t *state, void *user_data);
void dance_C_reset(tap_dance_state_t *state, void *user_data);

void on_dance_C(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_C);
		tap_code16(KC_C);
		tap_code16(KC_C);
	}
	if(state->count > 3) {
		tap_code16(KC_C);
	}
}

uint8_t dance_C_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_C_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_C_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_C); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_C)); break;
		case DOUBLE_TAP: register_code16(KC_C); register_code16(KC_C); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_C); register_code16(KC_C);
	}
}

void dance_C_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_C); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_C)); break;
		case DOUBLE_TAP: unregister_code16(KC_C); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_C); break;

	dance_state.step = 0;
    }
}

/*DANCE_V===============================================================================*/

void on_dance_V(tap_dance_state_t *state, void *user_data);
uint8_t dance_V_dance_step(tap_dance_state_t *state);
void dance_V_finished(tap_dance_state_t *state, void *user_data);
void dance_V_reset(tap_dance_state_t *state, void *user_data);

void on_dance_V(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_V);
		tap_code16(KC_V);
		tap_code16(KC_V);
	}
	if(state->count > 3) {
		tap_code16(KC_V);
	}
}

uint8_t dance_V_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_V_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_V_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_V); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_V)); break;
		case DOUBLE_TAP: register_code16(KC_V); register_code16(KC_V); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_V); register_code16(KC_V);
	}
}

void dance_V_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_V); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_V)); break;
		case DOUBLE_TAP: unregister_code16(KC_V); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_V); break;

	dance_state.step = 0;
    }
}

/*DANCE_Y===============================================================================*/

void on_dance_Y(tap_dance_state_t *state, void *user_data);
uint8_t dance_Y_dance_step(tap_dance_state_t *state);
void dance_Y_finished(tap_dance_state_t *state, void *user_data);
void dance_Y_reset(tap_dance_state_t *state, void *user_data);

void on_dance_Y(tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_Y);
		tap_code16(KC_Y);
		tap_code16(KC_Y);
	}
	if(state->count > 3) {
		tap_code16(KC_Y);
	}
}

uint8_t dance_Y_dance_step(tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_Y_finished(tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_Y_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_Y); break;
		case SINGLE_HOLD: register_code16(LCTL(KC_Y)); break;
		case DOUBLE_TAP: register_code16(KC_Y); register_code16(KC_Y); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_Y); register_code16(KC_Y);
	}
}

void dance_Y_reset(tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_Y); break;
		case SINGLE_HOLD: unregister_code16(LCTL(KC_Y)); break;
		case DOUBLE_TAP: unregister_code16(KC_Y); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_Y); break;

	dance_state.step = 0;
    }
}

/*Tap Dance action=============================================================================*/
tap_dance_action_t tap_dance_actions[] = {
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DANCE_X] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_X, dance_X_finished, dance_X_reset),
        [DANCE_C] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_C, dance_C_finished, dance_C_reset),
        [DANCE_V] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_V, dance_V_finished, dance_V_reset),
        [DANCE_Y] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_Y, dance_Y_finished, dance_Y_reset),
};



