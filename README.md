# EESTEC Olympics 11 Badge

# Electronic Event Badge

![Badge Image](badge_image.jpg)

## Overview

Welcome to the EESTEC Olympics 11 Badge github page! This repository contains all the resources and documentation for our electronic badge used in the event. These badges are designed to provide attendees with a unique, fun, interactive experience and are in no way tied into the main or side challanges of the contest.

## Features

- LED-s.
- Interactive buttons.
- Battery-powered for portability.
- Serial interface over USB Type-C.

## Getting Started

[!IMPORTANT]
The badge code will be published after Main Challange.

The event badge is essentialy a custom Arduino Uno board. Follow these steps to get started reprogramming your electronic event badge:

1. **Download Arduino IDE**: Download the Arduino development enviroment [here](https://www.arduino.cc/en/software)

2. **Set up the IDE**: The board uses a slightly different microcontroller, thusly you need to install it.
  - Open Arduino IDE
  - Install all drivers that pop up
  - Select "File" > "Preferences" > "Additional boards manager URLs" > paste this `https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json`
  - Hit ok and wait for the boards to download
  - Select "Tools" > "Board" > "Boards Manager..." > search and install "MiniCore"

3. **Programming Instructions**: Provide instructions for programming the badge, including the required tools and software.
  - In Arduino IDE select "File" > "Examples" > "01.Basics" > "Blink"
  - Select "Tools" > "Board" > "MiniCore" > "ATmega328"
  - Select "Tools" > "Port" > take note of what ports appear
  - Connect your badge to the computer with a USB Type-C cable
  - Select "Tools" > "Port" > select the port that has appeared
  - Select "Tools" > "Variant" > "328PB"
  - Select "Sketch" > "Upload"
  - After the upload is done, the led on the back should be blinking

5. **Header Assembly**(Optional): If your projects require them, you can solder two 20 pin female pin headers to the badge (2.54mm pitch).

## Documentation

- Detailed documentation can be found in the [Documentation](/docs) directory.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

If you have questions or need further assistance, feel free to contact us at [your.email@example.com].

## Acknowledgments

We'd like to acknowledge and thank all the contributors and supporters who have helped make this project possible.

## See It in Action

[Link to Demo Video or Image Gallery]

---

**Note**: Customize this README file to fit the specifics of your electronic event badge project. Be sure to provide detailed information on how to assemble, program, and use the badge, as well as any licensing and contribution information.
