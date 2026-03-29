# Splinter

[QMK](https://qmk.fm/) firmware for [splinter](https://github.com/andornaut/splinter-keyboard), a 62-key split columnar keyboard.

![splinter](https://raw.githubusercontent.com/andornaut/keyboards/main/v3/v3.jpg)

**Keyboard maintainer**: [andornaut](https://github.com/andornaut)

**Hardware supported**: [splitkb Liatris](https://splitkb.com/products/liatris)

## Versions

Version | Description | Firmware | Layout
--- | --- | --- | ---
[v4](https://github.com/andornaut/splinter-keyboard/tree/main/v4) | 62-keys. Liatris MCU with USB VBUS detection. | [branch/splinter](https://github.com/andornaut/qmk_firmware/tree/splinter/keyboards/splinter) | TBD
[v3](https://github.com/andornaut/splinter-keyboard/tree/main/v3) | 62-keys. KB2040 MCU. | [tags/splinter-v3.0](https://github.com/andornaut/qmk_firmware/tree/splinter-v3.0/keyboards/splinter) | [![v3](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v3/v3-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v3/v3.jpg)
[v2](https://github.com/andornaut/splinter-keyboard/tree/main/v2) | 62-keys. ATmega32U4 MCU. Symmetrical enclosures. | [tags/splinter-v2.0](https://github.com/andornaut/qmk_firmware/tree/splinter-2.0/keyboards/splinter) | [![v2](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v2/v2-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v2/v2.jpg)
[v1](https://github.com/andornaut/splinter-keyboard/tree/main/v1) | 61-keys. ATmega32U4 MCU. Asymmetrical enclosures. Traditional layout. | [tags/splinter-v1.0](https://github.com/andornaut/qmk_firmware/tree/splinter-1.0/keyboards/splinter) | [![v1](https://raw.githubusercontent.com/andornaut/splinter-keyboard/refs/heads/main/v1/v1-300width.jpg)](https://github.com/andornaut/splinter-keyboard/blob/main/v1/v1.jpg)

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

This enters the RP2040's native UF2 bootloader. Refer to the [Liatris pinout](https://docs.splitkb.com/product-guides/liatris/pinout) documentation.

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
# [671276.248574] usb 1-1: New USB device found, idVendor=feed, idProduct=0000, bcdDevice= 4.00
# Note the idVendor and idProduct values

sudo vim /etc/udev/rules.d/50-qmk.rules
# Add a line like:
# SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", ATTRS{idProduct}=="0000", TAG+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"

sudo udevadm control --reload
```

### Split keyboard reliability

The Liatris exposes `USB_VBUS_PIN` (GP19), which allows QMK to detect USB connectivity via a dedicated GPIO pin. This eliminates the `SPLIT_USB_DETECT` polling loop that the v3 KB2040 required, removing the ~2-second unresponsive window at boot and improving reliability after KVM switches.

Master/slave role assignment is now instant: the half connected to USB detects VBUS immediately and becomes master. The `SPLIT_WATCHDOG_ENABLE` and `SPLIT_WATCHDOG_TIMEOUT` settings are no longer needed.

Runtime reliability still depends on master-side connection throttling. Every scan cycle (~1000 Hz on RP2040), the master attempts serial communication with the slave. After `SPLIT_MAX_CONNECTION_ERRORS` consecutive failures, the master throttles to one retry per `SPLIT_CONNECTION_CHECK_TIMEOUT` ms — slave keypresses are dropped during this window.

The values in `config.h` address this:

Setting | Value | Reason
--- | --- | ---
`USB_VBUS_PIN` | GP19 | Liatris VBUS sense pin. Eliminates the `SPLIT_USB_DETECT` polling loop.
`SPLIT_MAX_CONNECTION_ERRORS` | 50 | The RP2040 scan cycle runs at ~1000 Hz, so the default of 10 errors accumulates in ~10ms — any brief TRRS glitch causes throttling. 50 errors tolerates ~50ms of consecutive failures before the master backs off.
`SPLIT_CONNECTION_CHECK_TIMEOUT` | 100ms | How long the master waits between reconnection attempts after flagging the slave as disconnected. 100ms gives fast recovery without flooding the scan loop. Setting this to 0 floods the scan loop with serial timeouts and drops keypresses.
