/*
  QUAD7SHIFT.cpp- Implementation of the library for driving 4 digits seven segment displays for modules that use 74HC595 shift registers.
  For ARDUINO UNO and NANO and ATtiny85 (or other ATtinys that use the same USI (Universal Serial Interface) module and same pins as the ATtiny85)
  Created by Alex Rosito, July 24, 2023.
  Released into the public domain.
  © Alex Rosito
*/

#include "QUAD7SHIFT.h"

// *** Instance constructor ***

QUAD7SHIFT::QUAD7SHIFT(bool displayType /*= COMMON_ANODE*/):
_type(displayType){
    /* Object instance constructor */
    _refreshRate = DEFAULT_REFRESH_RATE;
}
// Getter for the refreshRate memmber
unsigned long QUAD7SHIFT::getRefreshRate(){
    return _refreshRate;
}

// Setter for the refreshRate memmber
void QUAD7SHIFT::setRefreshRate(unsigned long refreshRate){
    _refreshRate = refreshRate;
} 

// *** Class private methods ***

// Function to reverse the order of bits in an 8-bit value
uint8_t QUAD7SHIFT::reverseBits(uint8_t b) {
    /* The purpose of this function is to reverse the order of bits in the input byte.
       This reversal is necessary because the TINYSPI library transfers only 8 bits in MSBFIRST
       (Most Significant Bits First) order, but this library requires the bits to be sent in 
       LSBFIRST (Least Significant Bits First)order to function correctly.
       It reads two reversed nibbles (4 bits each) from the lookup table and combines them to get 
       the reversed byte.
    */
    return pgm_read_byte(&(reverseLookUpTable[b & 0xF])) << 4 | pgm_read_byte(&(reverseLookUpTable[b >> 4]));
}

// Function to transfer a 16-bit result value to shift registers using SPI
void QUAD7SHIFT::transferDigit(uint16_t result) {
    // Set the latch pin LOW to prepare the shift registers for data transfer
    writePin(LATCHPIN,LOW);
        
    // Check if the code is being compiled for ATtiny85 or ATtiny13 microcontroller
    #if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__)
        // If compiling for ATtiny85 or similar MCUs, send the reversed lower byte first
        SPI.transfer(reverseBits(result & 0xFF));
        // Then, send the reversed higher byte second
        SPI.transfer(reverseBits((result >> 8) & 0xFF));
    #endif
    #if defined (__AVR_ATmega328P__) || (__AVR_ATmega168__)
        // For other microcontrollers, directly send the 16-bit result using SPI.transfer16
        SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
        SPI.transfer16(result);
        SPI.endTransaction();
   	#endif
	    
    // Set the latch pin HIGH to enable the shift registers to process the data
    writePin(LATCHPIN,HIGH);
    
    // At this point, the digit should be on and in its correct position in the display
}

// Function to print a digit on a 7-segment display at the specified position with an optional decimal point
void QUAD7SHIFT::printDigit(uint8_t number, uint8_t position, bool point) {
    // Calculate the bit mask to position the digit correctly on the display
    uint8_t digiBits = 0x10 << position;

    /* Read the bit pattern corresponding to the specified digit from the lookup table in program
       memory (Definition located in the QUAD7SHIFTata.h header file).
       The lookup table 'digits' contains the bit patterns for digits 0 to 9 (stored as 8-bit
       values) and other characters in program memory.
    */
    uint16_t theDigit = pgm_read_byte(&(digits[number])) << 8;

    // Set the decimal point bit if 'point' is true
    if (point) {
        theDigit |= 0x0100;
    }

    /* Depending on the display type (_type), prepare the result with the appropriate bit
       manipulation
       For common cathode displays (_type == true), complement the high byte of the digit pattern
       and set the specified position bits
       For common anode displays (_type == false), complement the position bits and set the digit
       pattern bits 
    */
    uint16_t result = _type ? (~theDigit & 0xFF00) | digiBits : (theDigit | (~digiBits & 0xFF));

    /* Transfer the result to the display by calling the 'transferDigit' function
       The 'transferDigit' function sends the 16-bit result to shift registers connected to the
       display 
    */
    transferDigit(result);
}

// Function to convert a floating-point number to fixed-point representation
// with a specified number of decimal places
unsigned int QUAD7SHIFT::fixedPointRepresentation(float number, uint8_t decimalPointPosition) {
    /* Read the power of 10 corresponding to the desired decimal point position
       from the lookup table 'powersOf10' in program memory (Definition located in the QUAD7SHIFTata.h
       header file).
       The 'powersOf10' table contains precomputed powers of 10 as 16-bit values.
    */
    unsigned int powerOf10 = pgm_read_word(&(powersOf10[decimalPointPosition]));

    /* Multiply the input 'number' by the power of 10 to shift the decimal point
       and convert the result to an unsigned integer (truncate the fractional part).
       To ensure correct rounding, add 0.5 to the result before converting to an integer
       This will round the number to the nearest integer instead of truncating it. 
    */
    return static_cast<unsigned int>(number * powerOf10 + 0.5);
}

// Function to print a number on a 4-digit seven-segment display with a specified decimal point position
void QUAD7SHIFT::printNumber(uint8_t number, uint8_t decimalPointPosition) {
    /* Print the given number on the 4-digit seven-segment display with a specified decimal point
      position 
    */
    
    uint8_t numberOfDigitsToDisplay = DIGITS_PER_MODULE;  // Variable to track the number of digits to display
    uint8_t digitsToPrint[numberOfDigitsToDisplay];  // Array to store the individual digits of the number

    digitsToPrint[0] = number % 10;  // Extract the rightmost digit (units place)
    digitsToPrint[1] = (number / 10) % 10;  // Extract the second rightmost digit (tens place)
    digitsToPrint[2] = (number / 100) % 10;  // Extract the third rightmost digit (hundreds place)
    digitsToPrint[3] = (number / 1000) % 10;  // Extract the fourth rightmost digit (thousands place)
    
    /* The following iteration is performed to eliminate preceding zeroes from a number.
       For example: If we want to display 10 we don't want the display to pring "0010"
    */
    // Iterate from the leftmost digit to the decimal point position or the leftmost non-zero digit.
    for (uint8_t i = 3; i >= decimalPointPosition; i--) {
        // If the current digit is 0 and not the decimal point position
        if (digitsToPrint[i] == 0 && i != decimalPointPosition) 
            numberOfDigitsToDisplay--;  // Decrement the number of digits to display
        else 
            break;  // Exit the loop if a non-zero digit is encountered
        
    }

    // MULTIPLEXING:
  
    unsigned long endtime = millis() + _refreshRate;  // Calculate the end time for printing (current time + refresh rate)
    uint8_t i = 0;  // Variable to track the current digit index during printing
    
    // Loop until the current time exceeds the end time.
    while (millis() <= endtime) {
  
        printDigit(digitsToPrint[i], i, i == decimalPointPosition);  // Print the current digit with the corresponding position and decimal point flag
        i = (i + 1) % numberOfDigitsToDisplay;  // Move to the next digit index in a circular manner
    }
}

// Function to get the index of a character in the 7-segment display lookup table
// Returns the index corresponding to the character for 7-segment display patterns
uint8_t QUAD7SHIFT::getTableIndex(char character) 
{
    // Check if the character is a digit (0 to 9)
    if (isdigit(character)) 
    {
        /* Convert the character to its corresponding digit value (0 to 9)
           and return the index corresponding to the digit in the lookup table
        */
        return character - '0';
    } 
    else 
    {
        // Convert the character to uppercase to handle both uppercase and lowercase inputs
        character = toupper(character);
        // Check the character against known specific characters to find their respective indices
        if (character == 'I') {
            return 1;
        } else if (character == 'Z') {
            return 2;
        } else if (character == 'S') {
            return 5;
        } else if (character == 'A') {
            return 10;
        } else if (character == 'B') {
            return 8;
        } else if (character == 'C') {
            return 12;
        } else if (character == 'D') {
            return 13;
        } else if (character == 'E') {
            return 14;
        } else if (character == 'F') {
            return 15;
        } else if (character == 'G') {
            return 16;
        } else if (character == 'H') {
            return 17;
        } else if (character == 'J') {
            return 18;
        } else if (character == 'L') {
            return 19;
        } else if (character == 'M') {
            return 20;
        } else if (character == 'O') {
            return 0;
        } else if (character == 'N') {
            return 21;    
        } else if (character == 'P') {
            return 22;
        } else if (character == 'Q') {
            return 9;    
        } else if (character == 'R') {
            return 23;
        } else if (character == 'T') {
            return 24;
        } else if (character == 'U') {
            return 25;
        } else if (character == 'V') {
            return 25;
        } else if (character == 'W') {
            return 28;    
        } else if (character == 'Y') {
            return 26;
        } else if (character == ' ') {
            return 27;
        } else {
            return 27;  // Return 27 (space) for any other characters
        }
    }
}

// *** Class public methods ***

// Function to initialize the 7-segment display
void QUAD7SHIFT::begin(unsigned long refreshRate) {
    
    // Initialize the Serial Peripheral Interface (SPI)
    setRefreshRate(refreshRate);
    
    SPI.begin();
    
    
    // Setting the MCU pins as outputs. Needed for the SPI communication.
    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
    #endif
    #if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__)
        DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2);
    #endif
    
}

// Function to print a string on the 4-digit seven-segment display
void QUAD7SHIFT::print(const char* displayString) {
    
    // Calculate the total number of digits to print and the pointLocation
    uint8_t totalDigitsToPrint = 0;
    uint8_t pointLocation = 0;
    uint8_t pointPosition = 0;
    // Iterate each character of the string
    uint8_t j = 1;
    for (uint8_t i = 0; displayString[i] != '\0'; i++) {
        //If the character is a period
        if (displayString[i] == '.') {
                pointPosition = i-j; // I keep track of where the point should be lighted up.
               pointLocation |= (1<<pointPosition); // I create a byte where each bit represents
                                                    // a point position to be displayed.
               j++;
      } else {
          //If the character is other but a period
            totalDigitsToPrint++; //I keep track of how many characters should be displayed.
        }
    }    
    // If the total of digits exceeds the amount of digits of the module throw an OVERFLOW error
    if (totalDigitsToPrint > DIGITS_PER_MODULE) {
        setRefreshRate(DEFAULT_REFRESH_RATE);
        print("OVF ");
        return;
    }
    
    // Create an array with size equal to the total of digits to display
    uint8_t digitsToPrint[totalDigitsToPrint];

    // Retrieve the digit value for each character in the string using the table index lookup
    for (uint8_t i = 0, j = 0; displayString[i] != '\0'; i++) {
        if (displayString[i] != '.') {
            digitsToPrint[j++] = getTableIndex(displayString[i]);
        }
    }

    // MULTIPLEXING:

    // Calculate the end time for printing (current time + refresh rate)
    unsigned long endtime = millis() + _refreshRate;
    
    // Calculate the index of the last digit in the array
    const uint8_t lastDigitIndex = totalDigitsToPrint - 1;

    // Loop until the current time exceeds the end time
    while (millis() <= endtime) {
        // Iterate over each digit to be displayed
        for (uint8_t i = 0; i < totalDigitsToPrint; i++) {
            // Calculate the index of the current digit from the rightmost position
            uint8_t digitIndex = lastDigitIndex - i;

            // Print the current digit or character at the corresponding digit index with or without a decimal point
            printDigit(digitsToPrint[i], digitIndex, (pointLocation >> i) & 0b1);
        }
    }
}

// Function to print a floating-point number on the 4-digit seven-segment display with a specified decimal point position
void QUAD7SHIFT::print(const float number, uint8_t decimalPointPosition) {
    // If the number is negative, print "NEG " and return
    if (number < 0) {
        setRefreshRate(DEFAULT_REFRESH_RATE);
        print("NEG ");
        return;
    }

    // Calculate the maximum allowed value based on the decimal point position
    unsigned int maxAllowedValue = pgm_read_word(&(powersOf10[5 - decimalPointPosition]));

    /* If the number exceeds the maximum allowed value, set the refresh rate to 1000 ms,
      print "OVF " (overflow), and return.
    */
    if (number >= maxAllowedValue) {
        setRefreshRate(DEFAULT_REFRESH_RATE);
        print("OVF ");
        return;
    }

    /* Convert the floating-point number to a scaled integer representation with the specified
       decimal point position
    */
    uint8_t scaledNumber = fixedPointRepresentation(number, decimalPointPosition);

    // Print the scaled number with the specified decimal point position
    printNumber(scaledNumber, decimalPointPosition);
}

// Function to print an unsigned integer on the 4-digit seven-segment display
void QUAD7SHIFT::print(const uint8_t number) {
    // If the number is negative, print "NEG" and return
    if (number < 0) {
        setRefreshRate(DEFAULT_REFRESH_RATE);
        print("NEG ");
        return;
    }

    // If the number is greater than 9999, print "OVF"
    // Otherwise, print the number without a decimal point
    if (number > 9999){
        setRefreshRate(DEFAULT_REFRESH_RATE);
        print("OVF ");
    }    
    else {
        // Convert the number to a scaled integer representation (since it's an integer, no decimal point is needed)
        uint8_t scaledNumber = number;
        // Print the scaled number without a decimal point
        printNumber(scaledNumber, 0);
    }
}