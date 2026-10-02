# KZR Firmware for Baofeng UV-K6x Radio

Firmware source code for the **Baofeng UV-K6x series** of radios.

This project is based on the CNT7 UV-K6x firmware source and contains modifications, fixes, and UI improvements developed for the **KZR Firmware** project.

The firmware is written in C and is designed to be compiled using GCC through the PlatformIO development environment.

---

## Features and Improvements

KZR Firmware includes several improvements and fixes to the original firmware, including:

* **Single Watch UI**

  * Added a Single Watch interface for improved radio status monitoring.

* **Type Mismatch Fixes**

  * Fixed type mismatches within the firmware source that could cause compilation issues or unexpected behavior.

* **Boot Menu Fix**

  * Fixed the broken boot menu functionality.

* **DTMF Hang Fix**

  * Fixed an issue with DTMF functionality that could cause the radio to hang or become unresponsive.

* **Band Switching Fix**

  * Fixed issues affecting band switching functionality.

---

## Firmware Diagram

![KZR Firmware Diagram](docs/diagram.png)


---

## Development Environment

### Visual Studio Code

The recommended development environment is **Visual Studio Code** with the PlatformIO IDE extension.

Download Visual Studio Code from:

https://code.visualstudio.com/

### PlatformIO IDE

1. Open Visual Studio Code.
2. Open the **Extensions** panel.
3. Search for **PlatformIO IDE**.
4. Install the PlatformIO IDE extension.

### Radio-Specific Platform

The UV-K6x firmware requires the CNT7-specific PlatformIO platform.

Open the **PlatformIO Core CLI** from:

**PlatformIO → Quick Access → Miscellaneous → PlatformIO Core CLI**

Then install the required platform:

```bash
pio pkg install -g -p https://github.com/cnt7/BAOFENG-UV-K6-Firmware
```

---

## Linux Setup

When developing on Linux, OpenOCD requires the appropriate udev rules for USB programming/debugging.

Copy the OpenOCD udev rules into `/etc/udev/rules.d/`:

```bash
sudo cp ~/.platformio/packages/tool-openocd-kd32/contrib/60-openocd.rules /etc/udev/rules.d/
```

Reload the udev rules:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Reconnect the programming/debugging hardware after applying the rules if necessary.

---

## Building the Firmware

1. Open the KZR Firmware project in Visual Studio Code.
2. Open the **PlatformIO** panel.
3. Select the appropriate firmware environment.
4. Click **Build**.

The firmware will be compiled and the resulting binary will be placed in the project's:

```text
./out/
```

directory.

---

## Uploading the Firmware

### Using the Baofeng Bootloader

The original Baofeng firmware can be uploaded using the `BFK6_Bootloader.exe` utility on Windows.

You will need:

* A Baofeng UV-K6x compatible programming cable
* A Windows computer
* `BFK6_Bootloader.exe`
* The compiled firmware binary

### Entering Firmware Update Mode

1. Power off the radio.
2. Connect the programming cable to the radio and computer.
3. Press and hold the **two orange side buttons**.
4. While holding both buttons, power on the radio.
5. The display should show:

```text
UPDATE
```

The radio is now in firmware update mode.

### Flashing the Firmware

1. Run `BFK6_Bootloader.exe`.
2. Click the `...` button.
3. Select the compiled firmware binary from the `./out/` directory.
4. Select the COM port used by the programming cable.
5. Click the large:

```text
Power on with side buttons pressed to Enter Upgrade
```

button.
6. Wait for the flashing process to complete before disconnecting or powering off the radio.

---

## Alternative Flashing Tool: BF-K6x-Flash

**BF-K6x-Flash** is an open-source command-line tool for flashing firmware to compatible Baofeng UV-K6x radios.

**Repository:** [BF-K6x-Flash on GitHub](https://github.com/sophiel-meow/BF-K6x-flash?utm_source=chatgpt.com)

### Installation

#### Linux

Install Rust and Cargo:

**Fedora:**

```bash
sudo dnf install rust cargo
```

**Debian/Ubuntu:**

```bash
sudo apt install rustc cargo
```

Clone the repository:

```bash
git clone https://github.com/sophiel-meow/BF-K6x-flash.git
cd BF-K6x-flash
```

Build the tool:

```bash
cargo build --release
```

The flashing tool will be located at:

```text
target/release/flash
```

### Flashing the Firmware

1. Connect the programming cable to the radio and computer.
2. Power off the radio.
3. Press and hold the **two orange side buttons**.
4. Power on the radio while holding both buttons.
5. The display should show:

```text
UPDATE
```

6. Find your programming cable's serial port:

```bash
ls /dev/ttyUSB*
```

For example:

```text
/dev/ttyUSB0
```

7. Flash the firmware:

```bash
./target/release/flash /path/to/firmware.bin /dev/ttyUSB0
```

For example:

```bash
./target/release/flash ./out/kzr-firmware.bin /dev/ttyUSB0
```

The default baud rate is **115200**.

You can also specify it manually:

```bash
./target/release/flash ./out/kzr-firmware.bin /dev/ttyUSB0 --baud 115200
```

Wait for the flashing process to finish before disconnecting or powering off the radio.

### Quick Start

For Linux, the complete process is:

```bash
git clone https://github.com/sophiel-meow/BF-K6x-flash.git
cd BF-K6x-flash
cargo build --release
./target/release/flash ./out/kzr-firmware.bin /dev/ttyUSB0
```

> **Note:** Replace `/dev/ttyUSB0` with the serial port assigned to your programming cable and replace `kzr-firmware.bin` with the actual firmware filename.


---

## Supported Radios

KZR Firmware is intended for compatible radios in the:

**Baofeng UV-K6x series**

Hardware compatibility may vary between different UV-K6x revisions. Always verify that the firmware image is intended for your specific radio before flashing.

---

## License

The original firmware source is released under the **BFPL-1.0** license.

See the [`LICENSE`](LICENSE) file for the complete license terms.

---

## Copyright

Original firmware:

**Copyright © 2024 Baofeng. All rights reserved.**

KZR Firmware modifications are provided according to the applicable terms of the original project license.

---

## Contributors

### Original Contributors

* **BD4VOW**
* **Starry Night Quintet**
* **CNT7**
* **DarkSoma**
* **OHMYTIME**
* **X**

### KZR Firmware Contributors

#### devKAIZER

Contributions to the KZR Firmware project:

* Single Watch UI
* Fix Type Mismatches
* Fix Broken Boot Menu
* Fix Broken DTMF Causing Hangs
* Fix Band Switching

---

## Acknowledgements

Special thanks to the developers and contributors of the original Baofeng UV-K6x firmware source and the CNT7 project for providing the foundation for further firmware development.

KZR Firmware builds upon that work with additional fixes, interface improvements, and functionality changes for compatible UV-K6x radios.

---

## Disclaimer

Firmware modification and flashing carries a risk of making the radio temporarily or permanently unusable.

Always:

* Verify that the firmware is compatible with your radio.
* Keep a backup of your original firmware when possible.
* Do not disconnect the radio during the flashing process.
* Ensure the programming cable is securely connected.
* Use appropriate radio frequencies and configurations according to applicable regulations.

**FLASH AT YOUR OWN RISK**
