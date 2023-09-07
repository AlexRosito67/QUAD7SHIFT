/*
  QUAD7SHIFTData.h - Complimentary header of th library for driving 4 digits seven segment displays for modules that use 74HC595 shiftregisters.
  For ARDUINO UNO and NANO and ATtiny85 (or other ATtinys that use the same USI (Universal Serial Interface) module and same pins as the ATtiny85)
  Created by Alex Rosito, July 24, 2023.
  Released into the public domain.
  © Alex Rosito
*/
#ifndef QUAD7SHIFTData_h
   
	#define QUAD7SHIFTData_h
    
        const unsigned int powersOf10[5] PROGMEM = {1, 10, 100, 1000, 10000};
        const uint8_t digits[29] PROGMEM = {
            0xFC, // 0 INDEX 0  'O' ASCII 79
            0x60, // 1 INDEX 1  ASCII 73
            0xDA, // 2 INDEX 2  ASCII 90
            0xF2, // 3 INDEX 3 
            0x66, // 4 INDEX 4 
            0xB6, // 5 INDEX 5  ASCII 83
            0xBE, // 6 INDEX 6 
            0xE0, // 7 INDEX 7 
            0xFE, // 8 INDEX 8 'B' ASCII 66
            0xF6, // 9 INDEX 9   ASCII 81
            0xEE, // A INDEX 10  ASCII 65
            0x3E, // b INDEX 11  ASCII 66
            0x9C, // C INDEX 12  ASCII 67
            0x7A, // d INDEX 13  ASCII 68
            0x9E, // E INDEX 14  ASCII 69 
            0x8E, // F INDEX 15 ASCII 70
            0xBC, // G INDEX 16  ASCII 71
            0x6E, // H INDEX 17  ASCII 72
            0X78, // J INDEX 18  ASCII 74
            0X1C, // l INDEX 19  ASCII 76
            0xAA, // M INDEX 20  ASCII 78
            0xEC, // N INDEX 21  ASCII 78 
            0XCE, // P INDEX 22  ASCII 80
            0x0A, // r INDEX 23  ASCII 82
            0x1E, // t INDEX 24  ASCII 84
            0x7C, // U INDEX 25  ASCII 85
            0x76, // Y INDEX 26 ASCII 89
            0X00, // space INDEX 27 ASCII 32  
            0x56  // W INDEX 28 ASCII 87
        };
        const uint8_t reverseLookUpTable[16] PROGMEM = {
            0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
            0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
        };
        
        
   
#endif
