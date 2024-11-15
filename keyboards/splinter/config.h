// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Must flash the left side at least once using: qmk flash -bl avrdude-split-left
#define EE_HANDS
