# Splinter

A 61-key split columnar keyboard.

![splinter](https://raw.githubusercontent.com/andornaut/keyboards/main/images/v1.jpg)

* [@andornaut/splinter-keyboard](https://github.com/andornaut/splinter-keyboard)

**Keyboard maintainer**: [andornaut](https://github.com/andornaut)

**Hardware supported**: Pro Micro ATmega32U4

## Documentation

* [Anatomy of a keymap.c](/docs/keymap.md)
* [Configurator](https://config.qmk.fm/#/test/)
* [Keycodes](/docs/keycodes.md)
* [Key overrides](https://docs.qmk.fm/#/feature_key_overrides)
* [Split keyboard](/docs/feature_split_keyboard.md)

## Usage

* [Make instructions](https://docs.qmk.fm/#/getting_started_make_guide)

```
make splinter
make splinter:flash
```

### udev

```
$ sudo vim /etc/udev/rules.d/50-qmk.rules
### Pro Micro Qwiic 5V/16MHz
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1b4f", ATTRS{idProduct}=="9206", TAG+="uaccess", ENV{ID_MM_DEVICE_IGNORE}="1"

$ sudo udevadm control --reload
```

## Bootloader

Enter the bootloader via either:

#### Bootmagic reset

1. Run `make splinter:default:flash`
1. Unplug the USB cable
1. While holding down the tilde ` key, plug in the USB cable

#### Physical reset button

1. run `make splinter:default:flash`
1. When it says "Waiting for USB serial port" and starts printing `*` characters, then press the reset button
1. Follow the steps below for your specific microcontroller ...

##### Pro Micro (USB-C) - 5V/16MHz - ATmega32U4

Either:

* Briefly press the reset button on/connected to the PCB, or
* Briefly short (connect with a wire) the RST and GND pins on the PCB

##### SparkFun Qwiic Pro Micro - USB-C (ATmega32U4)

* Press the reset button on the microcontroller twice in quick succession

If the above doesn't work, then try the following:

1. Before it says "Waiting for USB serial port", press and hold the reset button on the microcontroller
1. Once it starts printing `*` characters, release the reset button

## Developing

* [Complete newbs guide](https://docs.qmk.fm/#/newbs).
* [Setting up your QMK environment](https://docs.qmk.fm/#/newbs_getting_started)

```
python3 -m pip install --user qmk

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
qmk flash -bl avrdude-split-left
qmk flash -bl avrdude-split-right

# Thereafter
qmk flash
```
