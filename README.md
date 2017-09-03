# Arduino MCP492X

The Microchip [MCP4921](http://www.microchip.com/wwwproducts/en/en020398) and [MCP4922](http://www.microchip.com/wwwproducts/en/en020399) are 12 bit digital to analog converters with an SPI interface. The MCP4921 has one DAC output, the MCP4922 has two.

This library is built around the Arduino default SPI library and uses the designated SPI pins, in addition to a configurable chip select pin, passed in the constructor.

## Usage

### Wiring

Look up the designated SPI pins for your Arduino board, and wire up as follows:

| Arduino | MCP492X   | MCP4921 pin | MCP4922 pin |
|---------|-----------|-------------|-------------|
| SCK     | SCK       | 3           | 4           |
| MOSI    | SDI       | 4           | 5           |
| your CS | CS        | 2           | 3           |

Where "your CS" is whichever pin you'd like to use as chip select on your arduino board.

You can google "(your arduino board) pinout" to find pin diagrams. Look for a diagram that includes the SCK/MOSI/MISO designators. For example, for the Arduino Pro Micro board, you'd search "Arduino pro micro pinout"

### Code

This is the bare minimum to get started with one of these DACs in an Arduino project:

```cpp
#include <MCP49X.h> // Include the library

#define PIN_SPI_CHIP_SELECT_DAC 9 // Or any pin you'd like to use

MCP492X myDac(PIN_SPI_CHIP_SELECT);

void setup() {
  // put your setup code here, to run once:
  myDac.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Write any value from 0-4095
  myDac.analogWrite(2048);

  // If using an MCP4922, write a value to DAC B
  myDac.analogWrite(1, 3172);
}
```

#### Function descriptions

##### `begin()`

Initializes the library, by starting the SPI bus and configuring some settings.

It's required to call this in `setup()`.

##### `analogWrite(unsigned int value)`

Writes a 12-bit value to the DAC output. If this is on an MCP4922, it uses channel A.

##### `analogWrite(bool odd, unsigned int value)`

Writes a 12-bit value to a specific DAC output. If this is on an MCP4921, the value passed for `odd` is ignored. Otherwise, 0 selects the "even" DAC (A), and 1 selects the "odd" DAC (B).

`value` remains the 12-bit value you want to write.

##### `analogWrite(bool odd, bool buffered, bool gain, bool active, unsigned int value)`

Provides full access to all the control bits you can send to the DAC. Consult the data sheet for more information on each of the control bits.

