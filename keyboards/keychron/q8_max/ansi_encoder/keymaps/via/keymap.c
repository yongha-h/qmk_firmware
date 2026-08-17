/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    FN2,
    NAV,
};

// Corner key: tap = Caps Word, double-tap = Caps Lock
enum tap_dances {
    TD_CAPS,
};

static void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        caps_word_toggle();
    } else {
        tap_code(KC_CAPS);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, NULL),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_69(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,        KC_7,     KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,           KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,        KC_U,     KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,           KC_DEL,
        LCTL_T(KC_ESC), KC_A, KC_S,  KC_D,    KC_F,    KC_G,                 KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,        KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        TD(TD_CAPS), KC_LOPTN, KC_LCMMD, LT(NAV, KC_SPC),      MO(MAC_FN1), LT(FN2, KC_GRV),  KC_SPC,            KC_RCMMD,            KC_LEFT, KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_69(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,        KC_7,     KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,           KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,        KC_U,     KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,           KC_DEL,
        LCTL_T(KC_ESC), KC_A, KC_S,  KC_D,    KC_F,    KC_G,                 KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,            KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,        KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        TD(TD_CAPS), KC_LWIN, KC_LALT, LT(NAV, KC_SPC),        MO(WIN_FN1), LT(FN2, KC_GRV),  KC_SPC,            KC_RALT,             KC_LEFT, KC_DOWN,  KC_RGHT),

    [MAC_FN1] = LAYOUT_ansi_69(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTRL,KC_LNPAD,RGB_VAD, RGB_VAI,     KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,           RGB_TOG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,  _______,  _______,     _______, _______,  _______, _______,  _______,  _______,  _______,           _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,              _______,  _______, _______, _______,  _______,  _______,  _______,           KC_END,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,     _______,  NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,     _______,           _______,           _______,            _______, _______,  _______),

    [WIN_FN1] = LAYOUT_ansi_69(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, RGB_VAD, RGB_VAI,     KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,           RGB_TOG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,  _______,  _______,     _______, _______,  _______, _______,  _______,  _______,  _______,           _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,              _______,  _______, _______, _______,  _______,  _______,  _______,           KC_END,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,     _______,  NK_TOGG, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,     _______,           _______,           _______,            _______, _______,  _______),

   [FN2] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,    KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,           _______,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,   _______, _______,     _______,  _______, _______, _______,  _______,  _______,  _______,           _______,
        _______, _______,  _______,  _______, _______, _______,              _______,  _______, _______, _______,  _______,  _______,  _______,           _______,
        _______,           _______,  _______, _______, _______, BAT_LVL,     BAT_LVL,  _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,     _______,           _______,           _______,            _______, _______,  _______),

   [NAV] = LAYOUT_ansi_69(
        _______, _______,  _______,  _______, _______, _______, _______,     _______,  _______, _______, _______,  _______,  _______,  _______,           _______,
        _______, _______,  LALT(KC_RGHT), KC_END, _______, _______, _______, KC_PGUP,  _______, _______, _______,  _______,  _______,  _______,           _______,
        _______, KC_HOME,  _______,  KC_PGDN, _______, _______,             KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT,  _______,  _______,  _______,           _______,
        _______,           _______,  _______, _______, _______, LALT(KC_LEFT), LALT(KC_LEFT), _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,           _______,          _______,     _______,           _______,           _______,            _______, _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [FN2]      = {ENCODER_CCW_CW(_______, _______)},
    [NAV]      = {ENCODER_CCW_CW(_______, _______)},
};
#endif // ENCODER_MAP_ENABLE

// clang-format on

// HHKB-style navigation on Right Shift only (Left Shift keeps { : " ?)
const key_override_t rsft_lbrc_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_LBRC, KC_UP);
const key_override_t rsft_scln_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_SCLN, KC_LEFT);
const key_override_t rsft_quot_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_QUOT, KC_RGHT);
const key_override_t rsft_slsh_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_SLSH, KC_DOWN);

const key_override_t **key_overrides = (const key_override_t *[]){
    &rsft_lbrc_override,
    &rsft_scln_override,
    &rsft_quot_override,
    &rsft_slsh_override,
    NULL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
