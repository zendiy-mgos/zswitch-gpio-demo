# ZenSwitch-GPIO Demo 
## Overview
This is a [Mongoose-OS](https://mongoose-os.com/) demo firmware for using GPIO-enabled ZenSwitches. This firmware uses the native [zswitch-gpio](https://github.com/zendiy-mgos/zswitch-gpio) library.
## GET STARTED
Build up your device in few minutes just downloading, compiling and flashing this demo.

Clone the repo:
```bash
$ git clone https://github.com/zendiy-mgos/zswitch-gpio-demo my-zswitch-gpio-demo
$ cd my-zswitch-gpio-demo
```
Enable JavaScript demo (skip to continue with C/C++ demo) :
```yaml
sources:
# - src
  - src_js
libs:
  - origin: https://github.com/mongoose-os-libs/mjs
  - ...
```
Build the binary:
```bash
$ mos build --platform <device_platform>
```
Flash the firmware:
```bash
$ mos flash --port <port_name>
```
## Hardware
### Used components
 - Wemos D1 mini board
 - Wemos relay shield (2x)
 - 5V DC power supply (via min-USB cable or via external power supply)
### Wiring schema
![zswitch-gpio demo wiring schema](docs/zswitch-gpio-demo-sketch_bb.png)

