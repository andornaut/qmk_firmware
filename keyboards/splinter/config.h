// https://docs.qmk.fm/config_options#hardware-options

// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Must flash the left side at least once using: qmk flash -bl avrdude-split-left
#define EE_HANDS

// sets the number of milliseconds to pause after sending a wakeup packet. Disabled by default, you might want to set this to 200 (or higher) if the keyboard does not wake up properly after suspending.
#define USB_SUSPEND_WAKEUP_DELAY 200

// https://www.reddit.com/r/ErgoMechKeyboards/comments/zg5aiu/qmk_on_blackpill_need_to_unplugreplug_every_time/izgu7a7/
// #define SPLIT_USB_DETECT
