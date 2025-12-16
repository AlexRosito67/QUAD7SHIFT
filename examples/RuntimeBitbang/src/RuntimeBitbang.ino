#include <QUAD7SHIFT.h>

// Demonstrates runtime selection between hardware SPI and bit-banged SPI
QUAD7SHIFT display(COMMON_ANODE);

void setup()
{
    // faster refresh so the toggles are visible
    display.begin(200);

    // set bit-bang pins according to board (Arduino digital pins)
#if defined(__AVR_ATtiny85__)
    // Use PB1 (digital 1), PB3 (digital 3), PB4 (digital 4) as an example mapping
    display.setBitbangPins(1, 3, 4); // PB1, PB3, PB4
#else
    display.setBitbangPins(10, 11, 13);
#endif
}

void loop()
{
    // Hardware SPI mode for 3 seconds
    display.setBitbang(false);
    for (int i = 0; i < 3; ++i)
    {
        display.print("HW  ");
        delay(1000);
    }

    // Bit-bang SPI mode for 3 seconds
    display.setBitbang(true);
    for (int i = 0; i < 3; ++i)
    {
        display.print("BB  ");
        delay(1000);
    }

    // Quickly show numbers in both modes to observe behaviour
    for (int n = 0; n < 5; ++n)
    {
        display.setBitbang(false);
        display.print(n);
        delay(250);
    }
    for (int n = 0; n < 5; ++n)
    {
        display.setBitbang(true);
        display.print(n);
        delay(250);
    }
}
