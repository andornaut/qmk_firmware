// https://docs.qmk.fm/config_options#hardware-options

// Copyright 2024 andornaut (@andornaut)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// This method sets the keyboard's handedness by setting a flag in the persistent storage (EEPROM).
// This is checked when the controller first starts up, and determines what half the keyboard is, and how to orient the keyboard layout.
// Flash each half with its handedness target (qmk flash -bl uf2-split-left / uf2-split-right),
// which rewrites the stored side on every boot.
#define EE_HANDS

// https://docs.qmk.fm/platformdev_rp2040#double-tap
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms in which the double tap can occur.

// The Liatris exposes a USB VBUS sense pin (GP19), which allows QMK to detect
// USB connectivity via a dedicated GPIO rather than the SPLIT_USB_DETECT
// polling loop. This eliminates the ~2-second unresponsive window at boot and
// improves reliability after KVM switches. Requires a quality TRRS cable --
// a marginal cable can cause intermittent serial failures and key drops.
// With each module's VCC jumper at 3.6V, the half powered over the TRRS cable
// still reads GP19 low and runs as the secondary.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define USB_VBUS_PIN GP19

// Maximum number of failed communication attempts before the master throttles
// connection attempts. Set to 0 to disable. Each counted failure is one scan's
// transaction, retried up to 10 times with a 20ms (SERIAL_USART_TIMEOUT) handshake
// wait each, so with the other half absent one failure costs about 200ms of scan
// time. A brief glitch on a connected link is absorbed by those retries within one
// scan and never reaches this count. 10 (the QMK default) throttles a lone half
// after about 2s.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_MAX_CONNECTION_ERRORS 10

// How long (ms) the master blocks connection attempts after flagging the slave as
// disconnected; one attempt is allowed each time this interval elapses. Each
// attempt can stall the scan for the 20ms handshake timeout, so 500 (the QMK
// default) costs a lone half about 4% of its scan time. Do not set to 0: that
// floods the scan loop with serial timeouts and drops keypresses.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500

// SPLIT_WATCHDOG reboots the slave if it does not receive a ping from the
// master within SPLIT_WATCHDOG_TIMEOUT ms. Not needed with USB_VBUS_PIN and
// a quality TRRS cable. Previously caused periodic key drops during testing
// with a marginal cable -- the watchdog reboot cycle compounded the problem.
// Docs: https://docs.qmk.fm/features/split_keyboard#firmware-configuration
// #define SPLIT_WATCHDOG_ENABLE
// #define SPLIT_WATCHDOG_TIMEOUT 3000

// USB polling interval is set to 4ms in keyboard.json (usb.polling_interval).
// Default is 1ms (1000 Hz). 4ms (250 Hz) adds up to 3ms of input latency but
// reduces USB overhead. Set to 1 for lowest latency.
