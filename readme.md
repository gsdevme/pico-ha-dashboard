# PicoHaDashboard

A Pico W project with eink display to display Home Assistant information

# Requirements
### MacOS

```bash
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc cmake ninja
```

# Setup

Updates the [pico-sdk](https://github.com/raspberrypi/pico-sdk) sub-module, this may take a few minutes as its quite large.

```bash
git submodule update --init --recursive
```

# Build

Creates a new `build` directory and uses [ninja](https://ninja-build.org/) to build the .uf2 file.

```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```

Copy the .uf2 file from the `build` directory onto the pico to run

# Serial console (MacOS)

```bash
ls /dev/tty.*
screen /dev/tty.usbmodem0000000000001
```
