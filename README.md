# teensy-gampad
Use of a Teensy 2.0 to create a USB-gamepad.

Initially this was thought to be to play frets on fire, but then the code was used to create a normal gamepad (without guitar style).

## Building

Install avr-gcc:

```bash
# ArchLinux
sudo pacman -S avr-gcc
```

Build
```bash
make
```

## Download

Install teensy-loader-cli

```bash
# ArchLinux
yaourt -S teensy-loader-cli
```

Start teensy-loader-cli and press reset button:

```bash
teensy-loader-cli -mmcu=atmega32u4  -w guitar.hex
```
