# QUAD7SHIFT Library

Fix flickering and ghosting in 74HC595-driven 7-segment displays.

QUAD7SHIFT ensures stable multiplexed output by treating segment + digit selection as a single atomic 16-bit state and latching only once per update.

Designed for Arduino UNO/NANO and ATtiny — using hardware SPI (or USI) for uninterrupted transfers.


## If I saved you time you can show your appreciation

[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/AlexRosito67)


## Features

- Supports both **common anode** and **common cathode** configurations
- Print integers, floats with configurable decimal point, and strings
- Configurable refresh rate for display multiplexing
- **No external dependencies** — USI implemented directly for ATtiny platforms
- Compatible with ATmega-based Arduino UNO and NANO boards
- Compatible with ATtiny85, ATtiny25, ATtiny45, ATtiny261, ATtiny461 and ATtiny861
- PROGMEM used to store lookup tables — conserves RAM on small microcontrollers
- Overflow (OVF) and negative (NEG) error display built-in

## Table of Contents
- [The Problem](#the-problem)
- [The Solution](the-solution)
- [Installation](#installation)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Why QUAD7SHIFT](##why-QUAD7SHIFT?)
- [Methods](#methods)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)
- [Used in the wild](#used-in-the-wild)

## The Problem

Typical implementations use multiple shiftOut() calls or separate updates for segments and digit selection.

This creates intermediate states that can appear as:
- Ghosting between digits
- Uneven brightness
- Visible flicker under load or interrupts

## The Solution

QUAD7SHIFT:
- Builds a full 16-bit display state
- Sends it in one uninterrupted transfer (SPI/USI)
- Latches only once per update

No intermediate states ever reach the output.



## Installation

### Arduino IDE Library Manager (Recommended)

1. Open the Arduino IDE
2. Go to **Sketch** → **Include Library** → **Manage Libraries...**
3. Search for `QUAD7SHIFT`
4. Click **Install**

### Manual Installation

1. Download the library from [GitHub](https://github.com/AlexRosito67/QUAD7SHIFT)
2. Extract the ZIP file
3. Rename the folder to `QUAD7SHIFT`
4. Move it to your Arduino libraries folder:
   - macOS/Linux: `Documents/Arduino/libraries`
   - Windows: `My Documents\Arduino\libraries`

## Dependencies

### ATmega-based boards (Arduino UNO, NANO)
Built-in SPI library — no external dependencies required.

| Signal   | Pin |
|----------|-----|
| LATCHPIN | 10  |
| DATAPIN  | 11  |
| CLOCKPIN | 13  |

### ATtiny85, ATtiny25, ATtiny45, ATtiny261, ATtiny461, ATtiny861
No external dependencies — USI (Universal Serial Interface) implemented directly.

| Signal   | Pin       |
|----------|-----------|
| LATCHPIN | PB0 / 5   |
| DATAPIN  | PB1 / 6   |
| CLOCKPIN | PB2 / 7   |

## Usage
```cpp
#include <QUAD7SHIFT.h>

QUAD7SHIFT display(COMMON_ANODE);

void setup() {
  display.begin(); // Default refresh rate
  // display.begin(1000); // Custom refresh rate in milliseconds
}

void loop() {
  display.print(1234);     // Integer — max 9999
  display.print(12.34);    // Float — max 999.9
  display.print("GOOD");   // String — max 4 characters
  display.print("G.O.O.D."); // String with decimal points
}
```

## Why QUAD7SHIFT?
Most 74HC595 drivers flicker due to non-atomic updates and timing jitter.

This video shows the difference:
[![QUAD7SHIFT Demo](https://img.youtube.com/vi/2jVDQSVcXQ0/0.jpg)](https://www.youtube.com/watch?v=2jVDQSVcXQ0)

## Methods

| Method | Description |
|--------|-------------|
| `begin()` | Initialize with default refresh rate |
| `begin(refreshRate)` | Initialize with custom refresh rate (ms) |
| `getRefreshRate()` | Returns current refresh rate |
| `setRefreshRate(refreshRate)` | Sets refresh rate dynamically |
| `print(integer)` | Print integer — max 9999 |
| `print(float)` | Print float — max 999.9 |
| `print(string)` | Print string — max 4 chars, or 8 with decimal points |

## Examples

Check out the `examples` folder for usage examples and test sketches.

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for information about contributing.

## License

Please read [LICENSE.md](LICENSE.md).

## Used in the wild

- QUAD7SHIFT has been referenced in:

- DEV Community — deep dive into flickering causes and solutions
- Japanese technical analysis (lilting.ch) — latch boundary and multiplexing behavior
- CSDN (China) — ESP32-P4 SPI cascading reference

- This library is used as a **reference implementation** for stable 74HC595 display driving.

- QUAD7SHIFT was referenced in a technical article on [CSDN](https://wenku.csdn.net/answer/10mbatm661np) (China's largest developer community) covering ESP32-P4 SPI-driven 74HC595 cascading. The article cites QUAD7SHIFT as a reference implementation for cooperative shift register management with dynamic scanning on seven-segment displays.

- A deep-dive on why most 74HC595 display drivers flicker — and how QUAD7SHIFT avoids it — is available on [DEV Community](https://dev.to/alexrosito67/why-most-74hc595-display-drivers-flicker-and-how-quad7shift-avoids-it-without-trying-50eb).

- A technical analysis in Japanese covering the latch boundary mechanism, multiplexing stability, and platform comparisons (ESP32, Raspberry Pi, RP2040) was published on [lilting channel](https://lilting.ch/articles/74hc595-display-flicker-quad7shift) (April 29, 2026), citing QUAD7SHIFT as a reference implementation.

---

*Created by Alex Rosito — Valley Glen, Los Angeles, California*
