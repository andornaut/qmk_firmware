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

// The Liatris exposes a USB VBUS sense pin (GP19), which allows QMK to detect
// USB connectivity via a dedicated GPIO rather than the SPLIT_USB_DETECT
// polling loop. This eliminates the ~2-second unresponsive window at boot and
// improves reliability after KVM switches.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define USB_VBUS_PIN GP19

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

// Reboot the slave if it does not receive a ping from the master within
// this timeout. With USB_VBUS_PIN, the slave enters slave mode instantly,
// but the master may not have initialized serial yet. Without the watchdog,
// a missed initial connection is permanent until manual reset.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000

// USB polling interval is set to 4ms in keyboard.json (usb.polling_interval).
// Default is 1ms (1000 Hz). 4ms (250 Hz) adds up to 3ms of input latency but
// reduces USB overhead. Set to 1 for lowest latency.
