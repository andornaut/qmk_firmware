// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Helpful defines
#define GRAVE_MODS  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define _______ KC_TRNS

enum keyboard_layers {
 _BL, // Bottom Layer
 _FL  // Function Layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        // Left
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_SPC,  MO(_FL),

        // Right
        //KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        //KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS, KC_RSFT,
        //MO(_FL), KC_SPC
        MO(_FL), KC_SPC,  KC_BSPC,  KC_BSPC
    ),
    [_FL] = LAYOUT(
        // Left
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        _______, _______, KC_UP,   _______, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_DEL,  _______, _______,

        // Right
        //KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        //KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_PSCR, KC_SCRL, KC_PAUS,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_PSCR, KC_SCRL,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
        KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,
        //_______, _______
        _______, _______, KC_DEL,  KC_DEL
    )
};
