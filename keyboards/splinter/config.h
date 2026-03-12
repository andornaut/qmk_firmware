// https://docs.qmk.fm/config_options#hardware-options

// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Must flash the left side at least once using: qmk flash -bl uf2-split-left
#define EE_HANDS

// https://docs.qmk.fm/platformdev_rp2040#double-tap
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms in which the double tap can occur.

// The KB2040 has no USB_VBUS_PIN, so QMK automatically forces SPLIT_USB_DETECT
// on for all ChibiOS/ARM boards (see platforms/chibios/chibios_config.h).
// SPLIT_USB_DETECT uses a polling loop: each half polls for active USB
// communication for up to SPLIT_USB_TIMEOUT ms at boot. The half that detects
// USB becomes master; the other becomes slave. During this polling loop the
// half is completely unresponsive. Keeping SPLIT_USB_TIMEOUT at the default
// (2000ms) minimises the unresponsive window.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration

// Maximum number of failed communication attempts (one per scan cycle) before
// master throttles connection attempts. Set to 0 to disable.
// Default: 10. The RP2040 scan cycle runs at ~1000 Hz, so 10 errors accumulate
// in ~10ms — any brief TRRS glitch causes 100ms of dropped slave keypresses.
// 50 errors = ~50ms of consecutive failures tolerated before throttling.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_MAX_CONNECTION_ERRORS 50

// How long (ms) master blocks connection attempts after flagging slave as disconnected.
// One attempt is allowed each time this interval elapses. Do not set to 0 —
// that floods the scan loop with serial timeouts and drops keypresses.
// Default: 500. 100ms gives faster recovery without flooding the scan loop.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_CONNECTION_CHECK_TIMEOUT 100

// Enable watchdog on slave side to reboot if communication is lost.
// The watchdog timer starts after split_post_init() (i.e. after the USB
// polling loop), so it is independent of SPLIT_USB_TIMEOUT.
// Default (when unset): 3000ms if SPLIT_USB_TIMEOUT is not defined, else
//                       SPLIT_USB_TIMEOUT + 100ms (see split_util.c).
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000

// USB polling interval is set to 4ms in keyboard.json (usb.polling_interval).
// Default is 1ms (1000 Hz). 4ms (250 Hz) adds up to 3ms of input latency but
// reduces USB overhead. Set to 1 for lowest latency.
