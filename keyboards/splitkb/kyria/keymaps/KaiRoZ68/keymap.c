/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
 *
 * compile mit dem Befehl:
 * qmk compile -e CONVERT_TO=promicro_rp2040
 */
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _ARMA,
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
#define NUMP TG(_NUMPAD)
#define ADJU MO(_ADJUST)
#define WBSPC LCTL(KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */

[_QWERTY] = LAYOUT(
    QK_GESC,       KC_Q,            KC_W,           KC_E,           KC_R,          KC_T,                                                              TD(DANCE_Y),   KC_U,           KC_I,       KC_O,          KC_P,              TD(DANCE_5),
    KC_TAB,        KC_A,            KC_S,           KC_D,           KC_F,          KC_G,                                                              KC_H,          KC_J,         KC_K,      KC_L,  KC_SCLN,           KC_ENTER,
    OSM(MOD_LSFT),       KC_Z,    TD(DANCE_X),    TD(DANCE_C),    TD(DANCE_V),   KC_B,  XXXXXXX,          CW_TOGG,          NUMP,  		  XXXXXXX,KC_N,   KC_M,           KC_COMM,   KC_DOT,        KC_SLSH,   OSM(MOD_RSFT),
                                                    KC_MUTE,        OSM(MOD_LCTL), LOWER, LGUI_T(KC_ENTER) ,LALT_T(KC_ENTER), RALT_T(KC_DEL), KC_SPC, RAISE,  OSM(MOD_RCTL),  XXXXXXX
),

/* Lower */

[_LOWER] = LAYOUT(
    LSFT(KC_GRAVE),     LSFT(KC_1),      LSFT(KC_2),     LSFT(KC_3), LSFT(KC_4),    LSFT(KC_5),                                         LSFT(KC_6),     LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), _______,
    _______,            RALT(KC_8),      KC_NUBS,        RALT(KC_7), RALT(KC_NUBS), _______,                                            LSFT(KC_RBRC),  KC_MINUS,   KC_QUOTE,   KC_LBRC,    LSFT(KC_MINUS),    _______,
    _______,            RALT(KC_9),      LSFT(KC_NUBS),  RALT(KC_0), RALT(KC_MINS), _______,  _______,  _______,  CG_SWAP,  _______,    LSFT(KC_BSLS),  KC_EQUAL,   KC_RBRC,    KC_BSLS,    _______,    _______,
                                                         XXXXXXX,    _______,       _______ ,  _______,  _______,  _______,  _______,   LCTL(KC_BSPC),        _______,    XXXXXXX
),

/* Raise */

[_RAISE] = LAYOUT(
    KC_GRV,  TD(DANCE_1),   TD(DANCE_2),    TD(DANCE_3),    TD(DANCE_4),    KC_5,                                                   KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     _______,
    _______, KC_F11,        KC_F12,         KC_PGUP,        KC_PGDN,        KC_HOME,                                                KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_END,   _______,
    _______, KC_F1,         KC_F2,          KC_F3,          KC_F4,          KC_F5,      _______,  CG_NORM,  _______,  _______,      KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10 ,  _______,
                                            XXXXXXX,        _______,       _______,     _______,  _______,  _______,  _______,      _______, _______, XXXXXXX
),

/* Adjust (Lower + Raise) */

[_ADJUST] = LAYOUT(
    _______,          QK_BOOT, DB_TOGG, _______, _______, _______,                                        RGB_TOG,      RGB_MOD, RGB_HUI,  RGB_SAI, RGB_VAI, _______ ,
    QK_BOOTLOADER	, _______, _______, _______, _______, CG_TOGG,                                        _______,      _______, RGB_HUD,  RGB_SAD, RGB_VAD, QK_BOOTLOADER,
    QK_MAKE, _______, _______, _______, _______, _______, _______, _______,                     _______,  _______,      _______, _______,  _______, _______, _______, _______,
                               XXXXXXX, _______, _______, _______, _______,                     _______,  _______,  _______, _______,   XXXXXXX
  ),

/* Layer Numpad */

[_NUMPAD] = LAYOUT(
    _______,_______, KC_HOME , KC_UP,   KC_END,   _______,                                                      XXXXXXX,    KC_KP_7,  KC_KP_8,  KC_KP_9, KC_PSLS, _______,
    _______,_______, KC_LEFT, KC_DOWN,  KC_RIGHT, _______,                                                       XXXXXXX,    KC_KP_4,  KC_KP_5,  KC_KP_6, KC_PAST, KC_PENT,
    _______, _______, _______,  _______,  _______, _______, _______, _______,                 NUMP,  KC_NUM,    XXXXXXX,    KC_KP_1,  KC_KP_2,  KC_KP_3, KC_PMNS, _______,
                                XXXXXXX,  _______, _______, _______,  _______,              KC_PPLS, _______,   KC_KP_0,    KC_PDOT,  XXXXXXX
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
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



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

// 'glasses_smile_8', 128x32px
        static const char PROGMEM smile_cool[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x30, 0x10, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
0x18, 0x18, 0x10, 0x10, 0x30, 0x30, 0x20, 0x60, 0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x70, 0x18, 0x0c, 0x06, 0x03, 0x01,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c,
0x38, 0x70, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7c, 0x0f, 0x03, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xe0, 0xc0,
0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0,
0x00, 0x00, 0x01, 0x07, 0x1e, 0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x1f, 0x3f,
0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00,
0x06, 0x1e, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x0f, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x7c, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xc0, 0xf8, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0e, 0x1c, 0x30, 0x60, 0xc0, 0x80, 0x80,
0x08, 0x3e, 0x3f, 0xff, 0xff, 0x7f, 0x3f, 0x1e, 0x00, 0x00, 0x1c, 0x3f, 0x7f, 0xff, 0xff, 0x7f,
0x3e, 0x1c, 0x00, 0x00, 0x3e, 0x3f, 0xff, 0xff, 0x7f, 0x3f, 0x1e, 0x00, 0x80, 0xc0, 0x60, 0x70,
0x18, 0x0c, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
0x03, 0x06, 0x06, 0x0f, 0x0f, 0x18, 0x18, 0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x3f, 0x3f, 0x30,
0x30, 0x30, 0x10, 0x10, 0x18, 0x18, 0x0f, 0x0f, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev3.0 by Kai\n\n"), false);

        // Host Keyboard Layer Status∫∫
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("BASE\n"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("LOWER\n"), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("RAISE\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("CONFIG\n"), false);
                break;
            case _NUMPAD:
                oled_write_P(PSTR("NUMPAD\n"), false);
                break;
            case _ARMA:
                oled_write_P(PSTR("ARMA3\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("MOUSE\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

        /* Write Caps_Word_Status to OLEDs
        void caps_word_set_user(bool active)  {
            if (active) {
                oled_write_P(PSTR("CAPSWORD"),false);
            } else {
                oled_write_P(PSTR("nix"),false);
            }
        }
*/
    } else {
        // clang-format off
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            case _LOWER:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            case _RAISE:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));

                break;
            case _ADJUST:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            case _NUMPAD:
               oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            case _ARMA:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            case _MOUSE:
                oled_write_raw_P(smile_cool, sizeof(smile_cool));
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }


        // clang-format on

    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    return false;
}
#endif


bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

