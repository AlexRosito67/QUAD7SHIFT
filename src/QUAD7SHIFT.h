/*
  QUAD7SHIFT.h - Header of th library for driving 4 digits seven segment displays for modules that use 74HC595 shiftregisters.
  For ARDUINO UNO and NANO and ATtiny85 (or other ATtinys that use the same USI (Universal Serial Interface) module and same pins as the ATtiny85)
  Created by Alex Rosito, July 24, 2023.
  Released into the public domain.
  © Alex Rosito
*/

#ifndef QUAD7SHIFT_h
   
	#define QUAD7SHIFT_h
        #include <avr/pgmspace.h>
        #include "QUAD7SHIFTData.h"
		#define setBitValue(pos,val,var) \
			((val ? (var)|=_BV(pos) : (var)&=~_BV(pos)))
		#define getBit(var,pos) \
			(var >> pos) & 0b1
		#define setMode(pin,val) \
				setBitValue(pin,val,DDRB)
			#define writePin(pin,val) \
				setBitValue(pin,val,PORTB)
			#define readPin(pin) \
				((PINB & _BV(pin))>>(pin))	
			#define togglePin(pin) \
				( PINB = bit(pin) )					
		#include <Arduino.h>
		#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__)
            #include<tinySPI.h>
			#define LATCHPIN DDB0 // ATITINY PIN PB0 / PIN 5
			#define DATAPIN  DDB1 // ATITINY PIN PB1 / PIN 6
			#define CLOCKPIN DDB2 // ATITINY PIN PB2 / PIN 7
		#endif
        #if defined (__AVR_ATmega328P__) || (__AVR_ATmega168__)
			//Arduino
			#include <SPI.h>
			#define LATCHPIN DDB2  // ARDUINO UNO/NANO PIN 10
			#define DATAPIN  DDB3  // ARDUINO UNO/NANO PIN 11
			#define CLOCKPIN DDB5  // ARDUINO UNO/NANO PIN 13
		#endif	
		
		// Display types
		#define COMMON_ANODE 0
		#define COMMON_CATHODE 1
        #define DEFAULT_REFRESH_RATE 10000
        #define DIGITS_PER_MODULE  4
        
		// I define the QUAD7SHIFT class, its properties and methods prototypes
		class QUAD7SHIFT
		{
			private:
                // Class Attributes
                unsigned long _refreshRate;
                bool _type;
                                    
                // Class private methods        
                uint8_t reverseBits(uint8_t);
                void transferDigit(uint16_t);
                unsigned int fixedPointRepresentation(float,uint8_t);
                void printNumber(uint8_t, uint8_t);
                uint8_t getTableIndex(char);
                void printDigit( uint8_t , uint8_t , bool  );
 
            public:
                // Instance constructor
                QUAD7SHIFT(bool displayType = COMMON_ANODE);
                
                // Class public methods  
                void begin(unsigned long freshRate = DEFAULT_REFRESH_RATE);
                unsigned long getRefreshRate(void);
                void setRefreshRate(unsigned long);
                void print(const float, uint8_t);
                void print(const uint8_t );
                void print(const char* );
		};
#endif