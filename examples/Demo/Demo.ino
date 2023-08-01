/* Include the QUAD7SHIFT library 
 * (FFSD stands for: "Four digits Seven Segment Display")
 * For drivers that use 74HC595 shift Registers
*/ 
#include <QUAD7SHIFT.h>

// Define an instance of the QUAD7SHIFT class called myDisplay
QUAD7SHIFT myDisplay(COMMON_ANODE); // Change this to your display configuration (COMMON_ANODE or COMMON_CATHODE)
/* You can also define the instance like:                        
 * QUAD7SHIFT myDisplay();         // Sets up the display configuration as COMMON_ANODE by default   
*/

void setup(){
  myDisplay.begin(1000);   // Sets up initial conditions and begins SPI communication 
                           //(1000 stands for a refresh rate of 1000 milliseconds
  /* You can also do this:                        
   * myDisplay.begin();    // Sets up a refresh rate of 1000 millisenconds (1 second) by default   
  */
}

void loop(){
  myDisplay.print("CNT ");     // We are limited to 4 characters. Yes the space is a character
  myDisplay.print("DOWN");     // We have 4 characters
  myDisplay.print("S.T.R.T."); // But wait!, There are 7 characters!. Not quite. There are four but each has its period on.
  for(unsigned int i=0; i<6; i++){
    myDisplay.print(5-i);      // Printing an integer.
  }
  myDisplay.print(" .GO. ");   // Cool!
  for(uint8_t z=0; z<4; z++){
    myDisplay.setRefreshRate(pow(10,(3-z)));  // Changing the refresh rate of the display
    for(float j=0.0f; j<9.0f; j+=0.1)
      myDisplay.print(j,1);                   // Now we print a float number with a precision of 1 decimal point
      /*  But wait again!           
       *  We should consider the following:
       *   +----------+------------+
       *   | Decimals | Max number |
       *   |----------+------------|
       *   |     0    |   9999     |
       *   |     1    |   999.9    |
       *   |     2    |   99.99    |
       *   |     3    |   9.999    |
       *   +----------+------------+
       */
  }
  myDisplay.setRefreshRate(1000); // Going back to 1 second refresh rate
  myDisplay.print("STOP");        // Printing characters, 
  myDisplay.print("AGN ");        // Again
  myDisplay.print(" NOW");
}
