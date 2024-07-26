// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// https://docs.qmk.fm/#/feature_debounce_type
#define DEBOUNCE 10

// pcb v2
#define MATRIX_COL_PINS_RIGHT { B5, B4, D0, D4, C6, D7, E6 }
#define MATRIX_ROW_PINS_RIGHT { F7, B1, B3, B2, B6 }

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Must flash the left side at least once using: qmk flash -bl avrdude-split-left
#define EE_HANDS

// This configures the use of I2C support for split keyboard transport (AVR only).
//#define USE_I2C
#define SOFT_SERIAL_PIN D2

// Enabling this option changes the startup behavior to listen for an active
// USB communication to delegate which part is master and which is slave.
// With this option enabled and theres's USB communication, then that half
// assumes it is the master, otherwise it assumes it is the slave.
//
// Do not define SPLIT_USB_DETECT to avoid a bug where the keyboard isn't
// detected on boot unless it's disconnected and reconnected. Ref:
// https://old.reddit.com/r/olkb/comments/14cruyi/keyboard_doesnt_work_until_i_reconnect_it/jom8v2b/
// https://www.reddit.com/r/ErgoMechKeyboards/comments/11qxmn2/a_split_keyboard_made_with_qmk_will_work_only_if/
//#define SPLIT_USB_DETECT

// This will enable a software watchdog on any side delegated as slave and
// will reboot the keyboard if no successful communication occurs within
// SPLIT_WATCHDOG_TIMEOUT. This can be particularly helpful when
// SPLIT_USB_DETECT delegates both sides as slave in some circumstances.
//#define SPLIT_WATCHDOG_ENABLE
