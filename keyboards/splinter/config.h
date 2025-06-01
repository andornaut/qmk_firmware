// https://docs.qmk.fm/config_options#hardware-options

// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Must flash the left side at least once using: qmk flash -bl avrdude-split-left
#define EE_HANDS

// https://docs.qmk.fm/platformdev_rp2040#double-tap
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // Specify a optional status led by GPIO number which blinks when entering the bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
