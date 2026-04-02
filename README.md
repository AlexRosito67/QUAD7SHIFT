# QUAD7SHIFT Library

A lightweight Arduino library for driving 4-digit seven-segment displays using 74HC595 shift registers via SPI.


## If I saved you time you can show your appreciation

[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/AlexRosito67)


## Features

- Supports both **common anode** and **common cathode** configurations
- Print integers, floating-point numbers with decimal point positioning, and strings
- Configurable refresh rate for display multiplexing
- **No external dependencies** — USI implemented directly for ATtiny platforms
- Compatible with ATmega-based Arduino UNO and NANO boards
- Compatible with ATtiny85, ATtiny25, ATtiny45, ATtiny261, ATtiny461 and ATtiny861
- PROGMEM used to store lookup tables — conserves RAM on small microcontrollers
- Overflow (OVF) and negative (NEG) error display built-in

## Table of Contents

- [Installation](#installation)
- [Dependencies](#dependencies)
- [Usage](#usage)
- [Methods](#methods)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

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

---

*Created by Alex Rosito — Valley Glen, Los Angeles, California*
