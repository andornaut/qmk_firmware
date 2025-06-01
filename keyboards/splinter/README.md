# Splinter

QMK firmware for the [splinter-keyboard](https://github.com/andornaut/splinter-keyboard), which is a 62-key split columnar keyboard.

![splinter](https://raw.githubusercontent.com/andornaut/keyboards/main/v3/v3.jpg)

**Keyboard maintainer**: [andornaut](https://github.com/andornaut)

**Hardware supported**:

* [Adafruit KB2040](https://www.adafruit.com/product/5302)
  * [QMK platform docs](https://docs.qmk.fm/platformdev_rp2040)
  * [Pinout](https://learn.adafruit.com/adafruit-kb2040/pinouts)

## QMK Documentation

* [Configurator](https://config.qmk.fm/#/test/)
* [info.json documentation](https://github.com/qmk/qmk_firmware/blob/master/docs/reference_info_json.md) ([Schema](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema))
* [Split keyboard](https://docs.qmk.fm/features/split_keyboard)
* [Serial driver](https://docs.qmk.fm/drivers/serial)

## Flashing

* [Make instructions](https://docs.qmk.fm/#/getting_started_make_guide)

1. Run `make splinter:flash`

**Method (A) - Boot button**:

2. Unplug the USB cable
3. While holding down the "Boot" button on the microcontroller, plug the USB cable back in
4. Run `udisksctl mount -b /dev/disk/by-label/RPI-RP2` to mount the rp2040's flash storage to `/media/${USER}/RPI-RP2/`
   * QMK will automatically flash the new firmware then unmount `/media/${USER}/RPI-RP2/`

**Method (B) - Reset button**:

This will only work after the QMK firmware has been flashed at least once using Method (A).

2. Press the reset button on the microcontroller or PCB *twice* in quick succession
3. Run `udisksctl mount -b /dev/disk/by-label/RPI-RP2` to mount the rp2040's flash storage to `/media/${USER}/RPI-RP2/`
   * QMK will automatically flash the new firmware then unmount `/media/${USER}/RPI-RP2/`

## Developing

* [Complete newbs guide](https://docs.qmk.fm/#/newbs).
* [Setting up your QMK environment](https://docs.qmk.fm/#/newbs_getting_started)

```bash
python -m venv .venv
source .venv/bin/activate
python3 -m pip install qmk

qmk setup
qmk setup -H qmk_firmware
qmk config \
    compile.keyboard=splinter \
    compile.keymap=default \
    flash.keyboard=splinter \
    flash.keymap=default \
    new_keyboard.keyboard=splinter \
    new_keyboard.keymap=default
qmk new-keyboard
qmk compile

# First time to set EEPROM handedness
# Plug the *left* half in, and then run:
qmk flash -bl uf2-split-left
# Plug the *right* half in, and then run:
qmk flash -bl uf2-split-right

# Thereafter
qmk flash
```

### Configure `udev` rules to allow access to the keyboard

```bash
$ sudo dmesg --follow
# Connect device via USB and look for a line like:
# [671276.248574] usb 1-1: New USB device found, idVendor=2e8a, idProduct=8105, bcdDevice= 1.00
# Note the idVendor and idProduct values

$ sudo vim /etc/udev/rules.d/50-qmk.rules
### Pro Micro Qwiic 5V/16MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="9206", TAG+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"

$ sudo udevadm control --reload
```
