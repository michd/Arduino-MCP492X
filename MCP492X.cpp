#include <SPI.h>
#include "MCP492X.h"

MCP492X::MCP492X(uint8_t pinChipSelect) {
  _pinChipSelect = pinChipSelect;
}

void MCP492X::begin() {
  ::pinMode(_pinChipSelect, OUTPUT);
  ::digitalWrite(_pinChipSelect, 1);
  SPI.begin();
  _spiSettings = SPISettings(20000000, MSBFIRST, SPI_MODE0);
}

void MCP492X::analogWrite(unsigned int value) {
  analogWrite(0, value);
}

// Only applies to MCP4922
void MCP492X::analogWrite(bool odd, unsigned int value) {
  analogWrite(
    odd, // Pass channel
    0,   // Not buffered,
    1,   // Gain mode 1x (0 = 2x)
    1,   // Don't shut down output
    value);
}

// If you want full control, this method lets you set all config bits
// See MCP492X datasheet page 18 ("5.0 Serial interface") for details
void MCP492X::analogWrite(
  bool odd, bool buffered, bool gain, bool active, unsigned int value) {
  
  byte configBits = odd << 3 | buffered << 2 | gain << 1 | active;

  // Compose the first byte to send to the DAC:
  // the 4 control bits, and the 4 most significant bits of the value
  byte firstByte = configBits << 4 | (value & 0xF00) >> 8;
  // Second byte is the lower 8 bits of the value
  byte secondByte = value & 0xFF;

  _beginTransmission();
  SPI.transfer(firstByte);
  SPI.transfer(secondByte);  
  _endTransmission();
}

void MCP492X::_beginTransmission() {
  ::digitalWrite(_pinChipSelect, 0);
  SPI.beginTransaction(_spiSettings);
}

void MCP492X::_endTransmission() {
  SPI.endTransaction();
  ::digitalWrite(_pinChipSelect, 1);
}