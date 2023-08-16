# QUAD7SHIFT Library

This library provides functions for interfacing with 4-digit seven-segment displays in Arduino projects.

The QUAD7SHIFT library is a useful and well-organized library for interfacing with 4-digit seven-segment displays in Arduino projects. It provides functions to initialize the display, print numbers (including floating-point numbers with decimal point positioning), and print strings on the display. The library also supports both common anode and common cathode configurations, making it versatile for different types of seven-segment displays.

The library is written in a modular and object-oriented manner, with well-commented code that enhances readability and understanding. The comments provide clear explanations of the code's functionality, which is helpful for documentation purposes and for users to understand how the library works.

One notable feature is the use of PROGMEM to store data in program memory, which is a good optimization to conserve RAM. Additionally, the library provides support for both ATmega-based Arduino boards, ATtiny85, ATtiny25, ATtiny45, ATtiny261, ATtiny461 and ATtiny861, making it applicable to a broader range of Arduino platforms.

While the library appears to be well-designed and useful for driving 4-digit seven-segment displays, it's essential to test it thoroughly in real-world scenarios and consider edge cases to ensure its robustness and reliability. Users should also check for compatibility with their specific hardware and ensure they follow the documentation for proper usage.

Overall, the QUAD7SHIFT library is a valuable resource for Arduino projects involving 4-digit seven-segment displays and can save time and effort in developing such applications.

## Table of Contents

- [Installation](#installation)
- [Features](#features)
- [Usage](#usage)
- [Examples](#examples)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Arduino IDE Library Manager (Recommended)

1. Open the Arduino IDE.
2. Go to "Sketch" -> "Include Library" -> "Manage Libraries...".
3. In the Library Manager, search for "QUAD7SHIFT".
4. Click the "Install" button for the "QUAD7SHIFT" library.

### Manual Installation

1. Download the library from [GitHub](https://github.com/AlexRosito67/QUAD7SHIFT).
2. Extract the downloaded ZIP file.
3. Rename the extracted folder to "QUAD7SHIFT".
4. Move the "QUAD7SHIFT" folder to your Arduino libraries folder. By default, it is located in "Documents/Arduino/libraries" on macOS and Linux, "My Documents\Arduino\libraries" on Windows.

## Features

- Support for both common anode and common cathode 4-digit seven-segment displays.
- Print numbers (including floating-point numbers with decimal point positioning) and strings on the display.
- Configurable refresh rate for display updating.
- Works with ATmega-based Arduino UNO and NANO boards and ATtiny85 (or other ATtinys that use the same USI (Universal Serial Interface) module and same pins as the ATtiny85).

    [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/Ds3k1fd5XGU/0.jpg)](https://youtu.be/Ds3k1fd5XGU)  
  
    [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/2jVDQSVcXQ0/0.jpg)](https://youtu.be/2jVDQSVcXQ0) 
    
    [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/irkmbyNkbE4/0.jpg)](https://youtu.be/irkmbyNkbE4)  

## Examples

Check out the "examples" folder in this library for more usage examples and test sketches.

## Dependencies

- For ATmega-based Arduino boards: SPI library. 
    - LATCHPIN: ARDUINO UNO/NANO PIN 10
    - DATAPIN:  ARDUINO UNO/NANO PIN 11 
    - CLOCKPIN: ARDUINO UNO/NANO PIN 13
- For ATtiny85, ATtiny25, ATtiny45, ATtiny261, ATtiny461 and ATtiny861: TinySPI library.
    - LATCHPIN: ATITINY PIN PB0 / PIN 5
    - DATAPIN:  ATITINY PIN PB1 / PIN 6
    - CLOCKPIN: ATITINY PIN PB2 / PIN 7

Please make sure to install the appropriate library through the Arduino IDE Library Manager or by manually downloading it from their respective repositories.

## Contributing

Please read CONTRIBUTING.md for information about contributing.

## License

Please read LICENSE.md.


## Usage

```cpp
#include <QUAD7SHIFT.h>

// Create an instance of the QUAD7SHIFT class
QUAD7SHIFT display(COMMON_ANODE);

void setup() {
  // Initialize the QUAD7SHIFT library
  display.begin(); // Uses a default refresh rate of 1000
  /* Or you could use
   * display.begin(1000); 
   * which is the default display refresh rate, of course you can change it to your needs
  */
  display.print(1234);  // Print an integer number on the display
  display.print(12.34); // Print a float number on the display
  display.print("GOOD");      // Print a char string on the display    
  display.print("G.O.O.D.");  // Print a char string with dots on the display 
}

void loop() {
  // Add your code here
}

