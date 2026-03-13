# Splinter

[QMK](https://qmk.fm/) firmware for [splinter](https://github.com/andornaut/splinter-keyboard), a 62-key split columnar keyboard.

![splinter](https://raw.githubusercontent.com/andornaut/keyboards/main/v3/v3.jpg)

**Keyboard maintainer**: [andornaut](https://github.com/andornaut)

**Hardware supported**: [Adafruit KB2040](https://www.adafruit.com/product/5302)

## Versions

Version | Description | Firmware | Layout
--- | --- | --- | ---
[v3](https://github.com/andornaut/splinter-keyboard/tree/main/v3) | 62-keys. Symmetrical enclosures. Non-traditional placement of backspace and backslash keys. | [branch/splinter](https://github.com/andornaut/qmk_firmware/tree/splinter/keyboards/splinter) | [![v3](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v3/v3-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v3/v3.jpg)
[v2](https://github.com/andornaut/splinter-keyboard/tree/main/v2) | 62-keys. Symmetrical enclosures. Non-traditional placement of backspace and backslash keys. | [tags/splinter-v2.0](https://github.com/andornaut/qmk_firmware/tree/splinter-2.0/keyboards/splinter) | [![v2](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v2/v2-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v2/v2.jpg)
[v1](https://github.com/andornaut/splinter-keyboard/tree/main/v1) | 61-keys. Asymmetrical enclosures. Traditional layout. | [tags/splinter-v1.0](https://github.com/andornaut/qmk_firmware/tree/splinter-1.0/keyboards/splinter) | [![v1](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v1/v1-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v1/v1.jpg)

## Flashing

Both halves run their own copy of the firmware independently — there is no way to update one half over the TRRS link. Flash each half separately using the same steps:

1. Run `make splinter:flash`
1. Enter bootloader mode using one of the methods below ("Boot button" vs "Reset button")
1. Run `udisksctl mount -b /dev/disk/by-label/RPI-RP2` to mount the RP2040's flash storage to `/media/${USER}/RPI-RP2/`
   * QMK will automatically flash the new firmware then unmount `/media/${USER}/RPI-RP2/`
   * The keyboard will become unresponsive, so you'll need to use a second keyboard or SSH in from another computer
   * Alternatively, you could mount the RP2040's flash storage using a GUI disk manager such as `gnome-disks`, which can be done with only a mouse
1. Repeat for the other half

### Boot button

This enters the RP2040's native UF2 bootloader. Refer to the [KB2040 pinouts](https://learn.adafruit.com/adafruit-kb2040/pinouts) documentation.

Either:

1. Unplug the USB cable
1. While holding down the "Boot" button on the microcontroller, plug the USB cable back in

Or, if already plugged in:

1. Hold down the "Boot" button on the microcontroller
1. Press and release the "Reset" button
1. Release the "Boot" button

### Reset button (double-tap)

This uses QMK's [double-tap reset](https://docs.qmk.fm/platformdev_rp2040#double-tap) feature, which is enabled via `RP2040_BOOTLOADER_DOUBLE_TAP_RESET` in `config.h`. It only works after the QMK firmware has been flashed at least once using the boot button method.

1. Press the reset button on the microcontroller or PCB *twice* in quick succession

Note: after double-tapping reset, the keyboard enters bootloader mode and becomes unresponsive — see step 3 above for alternatives to run the mount command.

### First-time EEPROM handedness setup

The split halves use `EE_HANDS` to determine handedness. This must be set once per microcontroller.

```bash
# Plug the *left* half in, and then run:
qmk flash -bl uf2-split-left
# Plug the *right* half in, and then run:
qmk flash -bl uf2-split-right

# Thereafter
qmk flash
```

## Developing

```bash
python -m venv .venv
source .venv/bin/activate
python3 -m pip install qmk

qmk setup -H qmk_firmware
qmk config \
    compile.keyboard=splinter \
    compile.keymap=default \
    flash.keyboard=splinter \
    flash.keymap=default
qmk compile
```

### References

* [Config options](https://docs.qmk.fm/config_options)
* [Keycodes](https://docs.qmk.fm/keycodes)
* [keyboard.json schema](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema)
* [QMK CLI](https://docs.qmk.fm/cli)
* [RP2040 platform](https://docs.qmk.fm/platformdev_rp2040)
* [Serial driver](https://docs.qmk.fm/drivers/serial)
* [Setting up your QMK environment](https://docs.qmk.fm/newbs_getting_started)
* [Split keyboard](https://docs.qmk.fm/features/split_keyboard)

## Troubleshooting

### Debug console

The `console` feature is enabled in `keyboard.json`, and `process_record_user` in `keymap.c` logs key events when the console is active. To read the debug output:

1. Build and flash the firmware: `qmk flash`
1. Run `qmk console` to connect to the keyboard's HID console and view key event logs

To enable additional QMK debug output (matrix scanning, split transport, etc.), add the following to `keymap.c` in `keyboard_post_init_user`:

```c
void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix = true;   // Log matrix scan events
    // debug_keyboard = true; // Log keyboard-level events
}
```

To disable the console (saves firmware size and a small amount of scan-cycle overhead), set `"console": false` in `keyboard.json` and reflash.

### Configure udev rules

```bash
sudo dmesg --follow
# Connect device via USB and look for a line like:
# [671276.248574] usb 1-1: New USB device found, idVendor=2e8a, idProduct=8105, bcdDevice= 1.00
# Note the idVendor and idProduct values

sudo vim /etc/udev/rules.d/50-qmk.rules
# Add a line like:
# SUBSYSTEMS=="usb", ATTRS{idVendor}=="2e8a", ATTRS{idProduct}=="8105", TAG+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"

sudo udevadm control --reload
```

### Split keyboard reliability

The KB2040 has no hardware USB VBUS sense pin, so QMK automatically forces [`SPLIT_USB_DETECT`](https://docs.qmk.fm/features/split_keyboard#firmware-configuration) on for all ChibiOS/ARM boards that lack `USB_VBUS_PIN` (see `platforms/chibios/chibios_config.h`). This cannot be disabled without a PCB hardware modification.

`SPLIT_USB_DETECT` determines master/slave roles by a software timing race: at boot, each half polls for active USB communication for up to `SPLIT_USB_TIMEOUT` milliseconds. The half that detects USB becomes master; the other becomes slave. **During this polling loop the half is completely unresponsive.** If neither half detects USB within the timeout, both declare themselves slaves, and the keyboard does not function until `SPLIT_WATCHDOG_ENABLE` triggers a reboot and they retry.

The watchdog timer starts after `split_post_init()` — i.e. after the USB polling loop finishes — so `SPLIT_WATCHDOG_TIMEOUT` is independent of `SPLIT_USB_TIMEOUT`. The watchdog is only relevant at startup: once the slave receives its first ping from the master, it is permanently satisfied and does not recover from runtime disconnects. Runtime recovery depends on master-side connection throttling (`SPLIT_MAX_CONNECTION_ERRORS` / `SPLIT_CONNECTION_CHECK_TIMEOUT`).

Known failure modes and symptoms:

* Plugging USB into one half sometimes works, sometimes doesn't — USB enumeration took longer than `SPLIT_USB_TIMEOUT`
* One half appears dead at startup — that half lost the USB detection race; `SPLIT_WATCHDOG_ENABLE` reboots it so it can retry. Increasing `SPLIT_USB_TIMEOUT` makes this worse by extending the unresponsive polling window per reboot cycle.
* Slave keypresses intermittently drop — a brief TRRS glitch caused `SPLIT_MAX_CONNECTION_ERRORS` to be reached, triggering master-side throttling. The RP2040 scan cycle is ~1000 Hz, so the default of 10 errors accumulates in ~10ms.
* After switching KVM inputs, the keyboard takes several seconds to respond — USB re-enumeration on the master side triggers re-detection; recovery time depends on `SPLIT_USB_TIMEOUT` + watchdog cycle. Keeping `SPLIT_USB_TIMEOUT` low helps but cannot eliminate the delay
* Setting `SPLIT_CONNECTION_CHECK_TIMEOUT 0` floods the scan loop with serial timeouts and causes keypresses to be dropped

The values in `config.h` address this:

Setting | Value | Reason
--- | --- | ---
`SPLIT_USB_TIMEOUT` | 2000ms (default) | Kept at default to minimise the unresponsive window per reboot. Increasing it makes the "one half dead" symptom worse because the slave spends more time in the polling loop each reboot cycle.
`SPLIT_WATCHDOG_TIMEOUT` | 3000ms | Reboots the slave quickly if it never receives a first ping from the master after boot. Once the first ping is received the watchdog is permanently satisfied and plays no further role.
`SPLIT_MAX_CONNECTION_ERRORS` | 50 | The RP2040 scan cycle runs at ~1000 Hz, so the default of 10 errors accumulates in ~10ms — any brief TRRS glitch causes throttling. 50 errors tolerates ~50ms of consecutive failures before the master backs off.
`SPLIT_CONNECTION_CHECK_TIMEOUT` | 100ms | How long the master waits between reconnection attempts after flagging the slave as disconnected. 100ms gives fast recovery without flooding the scan loop. Setting this to 0 floods the scan loop with serial timeouts and drops keypresses.
