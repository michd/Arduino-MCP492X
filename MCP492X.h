/*
 * MCP4921/MCP4922 12 bit DAC Library
 * By MichD
 *
 * GitHub: https://github.com/michd/Arduino-MCP492X
 *
 * The Microchip MCP4921 and MCP4922 are 12 bit digital to analog converters
 * with an SPI interface. The MCP4921 has one DAC output, the MCP4922 has two.
 *
 * This library is built around the Arduino default SPI library and uses the
 * designated SPI pins, in addition to a configurable chip select pin, passed
 * in the constructor.
 * Look up the designated pins for your arduino board, and wire up as follows:
 *
 * | Arduino | MCP492X   | MCP4921 pin | MCP4922 pin |
 * |---------|-----------|-------------|-------------|
 * | SCK     | SCK       | 3           | 4           |
 * | MOSI    | SDI       | 4           | 5           |
 * | your CS | CS        | 2           | 3           |
 * 
 * Where "your CS" is whichever pin you'd like to use as chip select on
 * your arduino board.
 */

#include <Arduino.h>
#include <SPI.h>

// Ensure we don't double-define the functionality
#ifndef MCP492X_h
#define MCP492X_h

class MCP492X {
  public:
    // Constructor, takes the chip select pin
    // Use outside any functions:
    // `MCP492X myDac(pinNumber);`
    MCP492X(uint8_t);

    // Initilize, starts the SPI bus. Call in setup()
    // Example:
    // ```
    // void setup() {
    //   myDac.begin();
    // }
    //
    void begin();
    
    // Writes a 12 bit value to the output.
    // If on the MCP4922, defaults to DAC output 0 (A).
    // Example:
    // ```
    // myDac.analogWrite(1234);
    // ```
    void analogWrite(unsigned int);       // Write a 12 bit value

    // Writes a 12 bit value to a given DAC output (0 or 1 / A or B)
    // Param 1 = DAC selection
    // Param 2 = 12 bit value
    // Example:
    // ```
    // myDac.analogWrite(1, 4095);
    // ```
    void analogWrite(bool, unsigned int); // Write a 12 bit value to a specific output (only MCP4922)

    // Writes a 12 bit value to a given DAC output (0 or 1 / A or B),
    // and allows setting every config bit individually.
    // Param 1 = DAC selection
    // Param 2 = buffer input
    // Param 2 = gain mode (1 = 1x, 0 = 2x)
    // Param 3 = shut down output (1 = active, 0 = shutdown)
    // Param 4 = 12 bit value
    // Example:
    // ```
    // myDac.analogWrite(1, 0, 1, 1, 2480);
    // ```
    void analogWrite(bool, bool, bool, bool, unsigned int); // Full control over control bits

  private:
    // Internal fields/methods you should not need to worry about.
    // Holds onto the chip select pin number
    uint8_t _pinChipSelect;

    // SPI settings for this chip, set up in begin()
    SPISettings _spiSettings;

    // Internal helpers to start/end transmission
    void _beginTransmission();
    void _endTransmission();
};

#endif // MCP921X_h
