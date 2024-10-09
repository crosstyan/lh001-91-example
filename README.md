# [LH001-91](http://en.legendsemi.com/product_2/1043097573976657920.html) evaluation example

[LH001-91](http://en.legendsemi.com/product_2/1043097573976657920.html) is a
high-precision and low-cost analog front end: it supports EEG, ECG measurement
and other functions, and integrates low-noise PGA and 24-bit, 8kSPS
analog-to-digital converter on-chip. On-chip signal sources are integrated for
continuous lead disconnection detection, channel path testing, and temperature
measurement. In addition, the right leg drive output function that can realize
closed-loop control is also integrated on the chip to improve the loop CMRR (Common Mode Rejection Ratio).

The MCU should be [GD32F330CBT6](https://www.gigadevice.com/product/mcu/mcus-product-selector/gd32f330cbt6).

Using standard peripherals libraries (SPL) for GD32F3x0. This project use [CMake](https://cmake.org/) as build system.

## Usage

If you don't have a toolchain for ARM, you can
use [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).

```
mkdir build
cd build
cmake .. -GNinja -DTOOLCHAIN_PREFIX=<path to toolchain>
```

## flashing

```bash
probe-rs download --chip GD32F330CB build/lh001.elf
```

```bash
# debug
/opt/arm-gnu-toolchain-13.2/bin/arm-none-eabi-gdb build/lh001.elf -ex 'target extended-remote localhost:4242'
```

## References

See also [CommunityGD32Cores/ArduinoCore-GD32](https://github.com/CommunityGD32Cores/ArduinoCore-GD32).
See the [og](https://github.com/HQU-gxy/lh001-91-example/tree/og) branch for the original code provided by the vendor.

- [CommunityGD32Cores/gd32-pio-spl-package](https://github.com/CommunityGD32Cores/gd32-pio-spl-package)
- [CommunityGD32Cores/gd32-pio-projects](https://github.com/CommunityGD32Cores/gd32-pio-projects)
- [CommunityGD32Cores/platform-gd32](https://github.com/CommunityGD32Cores/platform-gd32)
- [charlesnicholson/nanoprintf](https://github.com/charlesnicholson/nanoprintf)
- [MaJerle/lwprintf](https://github.com/MaJerle/lwprintf)
