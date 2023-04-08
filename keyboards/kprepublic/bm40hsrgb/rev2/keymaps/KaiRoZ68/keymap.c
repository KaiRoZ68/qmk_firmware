/* Copyright 2020 tominabox1
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
  _NUMPAD
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMP TG(_NUMPAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty */

[_QWERTY] = LAYOUT_ortho_4x12_1x2uC(
    QK_GESC,       KC_Q,    KC_W,    KC_E,              KC_R,    KC_T,    KC_Y,    KC_U,            KC_I,           KC_O,           KC_P,    KC_BSPC,
    KC_TAB,        KC_A,    KC_S ,   KC_D,              KC_F,    KC_G,    KC_H,    KC_J,            KC_K,           KC_L,           KC_SCLN, KC_ENTER,
    OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,              KC_V,    KC_B,    KC_N,    KC_M,            KC_COMM,        KC_DOT,         KC_SLSH, OSM(MOD_RSFT),
    OSM(MOD_LCTL), NUMP,    KC_LGUI, LALT_T(KC_INS),    LOWER,   KC_SPC,           RAISE,           RALT_T(KC_DEL), C_S_T(KC_SPC),  CG_TOGG, OSM(MOD_RCTL)
),

/* Lower */

[_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    LSFT(KC_GRAVE),     LSFT(KC_1),      LSFT(KC_2),     LSFT(KC_3), LSFT(KC_4),    LSFT(KC_5), LSFT(KC_6),     LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), _______,
    _______,            RALT(KC_8),      KC_NUBS,        RALT(KC_7), RALT(KC_NUBS), _______,    LSFT(KC_RBRC),  KC_MINUS,   KC_QUOTE,   KC_LBRC,    _______,    _______,
    _______,            RALT(KC_9),      LSFT(KC_NUBS),  RALT(KC_0), RALT(KC_MINS), _______,    _______,        KC_EQUAL,   KC_RBRC,    KC_BSLS,    _______,    _______,
    _______,            _______,         _______,        _______,    _______,       _______,                    _______,    _______,    _______,    _______,    _______
),

/* Raise */

[_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    KC_GRV,  KC_1,    KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     _______,
    _______, KC_F11,  KC_F12, KC_PGUP, KC_PGDN,  KC_HOME, KC_LEFT, KC_DOWN, KC_UP,      KC_RIGHT, KC_END,   _______,
    _______, KC_F1,   KC_F2,     KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10 ,  _______,
    _______, _______, _______,   _______, _______, _______,          _______, KC_MNXT,  KC_VOLD,  KC_VOLU,  KC_MPLY
),

/* Adjust (Lower + Raise) */

[_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD,  _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______,  _______,  _______, _______
  ),


/* Layer Numpad */

[_NUMPAD] = LAYOUT_ortho_4x12_1x2uC(
    _______, KC_HOME , KC_UP,   KC_END,   _______, _______, _______,  KC_KP_7,  KC_KP_8,  KC_KP_9, KC_PSLS, _______,
    _______, KC_LEFT, KC_DOWN,  KC_RIGHT, _______, _______, _______,  KC_KP_4,  KC_KP_5,  KC_KP_6, KC_PAST, KC_PENT,
    _______, _______, _______,  _______,  _______, _______, _______,  KC_KP_1,  KC_KP_2,  KC_KP_3, KC_PMNS, _______,
    NUMP   , _______, _______,  _______,  _______, _______,           KC_KP_0,  KC_PDOT,  KC_DOT , KC_PPLS, KC_NUM
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
