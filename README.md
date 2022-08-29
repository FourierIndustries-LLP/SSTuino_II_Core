# SSTuino II Core

![License](https://img.shields.io/github/license/FourierIndustries-LLP/SSTuino_II_Core) ![Linting Status](https://github.com/FourierIndustries-LLP/SSTuino_II_Core/actions/workflows/arduino_ci.yml/badge.svg)

> The Arduino core powering the SSTuino II

![Pinout](./SSTuino%20II%20Rev%20A%20Pinout%20Final.png)

- [x] ⭕️ Arduino Core (Software)
- [ ] 📟 Hardware / CAD Files
- [ ] 📥 Installer
- [ ] 📚 Library
- [ ] 🛠 Helper Scripts
- [ ] 📖 Documentation
- [ ] ❓ Miscellaneous / Uncategorized

This repository is the Arduino core that powers the SSTuino II, a compact and easy-to-use 8-bit IoT enabled microcontroller made by FourierIndustries LLP.

## Directories

* `megaavr/` - Arduino source code for this core

## Installation

### Boards Manager Installation

* Open Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**:
    ```
    https://fourierindustries-llp.github.io/SSTuino_II_Core/package_FourierIndustries-LLP_SSTuino_II_Core_index.json
    ```
* Separate the URLs using a comma ( **,** ) if you have more than one URL
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **SSTuino II** entry and click on it.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

### Manual Installation

Click on the "Download ZIP" button. Extract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**" (for macOS). Create the "hardware" folder if it doesn't exist.

In addition, you will need to manually install the following libraries:

* [WiFiNINA-SSTuino](https://github.com/FourierIndustries-LLP/WiFiNINA-SSTuino)
* [ArduinoHTTPClient](https://github.com/arduino-libraries/ArduinoHttpClient)
* [arduino-mqtt](https://github.com/256dpi/arduino-mqtt)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [RBD_Timer](https://github.com/alextaujenis/RBD_Timer)

Open Arduino IDE and a new category in the boards menu called "SSTuino II" will show up.

## Usage

This Arduino core functions mostly identically to all other Arduino cores, with some extensions specific to the ATmega4809 and its peripherals.

The following high-quality libraries for ATmega4809-specific extensions were written by [MCUdude](https://github.com/MCUdude), and are included in this core as well:

- Comparator
- Event
- Logic

## Documentation ![Inline docs](http://inch-ci.org/github/dwyl/hapi-auth-jwt2.svg?branch=master)

Please refer to the [FourierIndustries Knowledge Base](https://knowledge.fourier.industries). Beginners can refer to the Essentials Track, which has tutorials on the basics of an Arduino, and the fundamentals of IoT.

## Known issues

There are no known issues in this repo. 

## Contributing

If you encounter any issues with this repository, please do not hesitate to open an issue on this repository's Issue Tracker.

This was based on the awesome [MegaCoreX](https://github.com/MCUdude/MegaCoreX) made by [MCUdude](https://github.com/MCUdude) and is licensed as LGPL-2.1. 
