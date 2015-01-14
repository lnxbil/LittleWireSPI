#ifndef __LITTLEWIRESPI_H__
#define __LITTLEWIRESPI_H__

#include <unistd.h>

// forward declarations from littlewire.h
#define LOW     0
#define HIGH    1
#define INPUT   1
#define OUTPUT  0


typedef unsigned char byte;
typedef unsigned char uint8_t;

void connect();

void digitalWrite(unsigned char pin, unsigned char state);
void pinMode(unsigned char pin, unsigned char direction);


unsigned int getSPICalls();

class LittleWireSPI {
public:
  static byte transfer(byte _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);
};

#endif
