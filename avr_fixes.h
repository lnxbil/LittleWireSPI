#ifndef __AVR_FIXES_H__
#define __AVR_FIXES_H__

#include <unistd.h>

#define delayMicroseconds usleep
#define delay(sec) usleep(1000 * sec)

typedef unsigned char byte;

unsigned long millis();
unsigned long micros();

#endif
