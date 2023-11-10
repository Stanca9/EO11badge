# EESTEC Olympics 11 Badge

## Overview

Welcome to the EESTEC Olympics 11 Badge github page! This repository contains all the code and documentation for our electronic badge used in the event. These badges are designed to provide attendees with a unique experience and are in no way tied into the main or side challenges of the contest. They are designed to act as Arduino-like development boards that can be used as such after the event. Just solder on some header pins on the back and get started! (And if you ask nicely we might even be able to do that for you)

## Features

- LED-s
- Programmable buttons
- Battery-powered

## Getting Started

**Follow these steps to get started reprogramming your electronic event badge:**

1. **Download Arduino IDE**: Download the Arduino development enviroment [here](https://www.arduino.cc/en/software), then install it.

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

## Contact information

The badge is designed and programmed by me, Stanca Robert-Lucian. Reach me at: `robert@stanca.eu` or `robertlucian.stanca@gmail.com`
