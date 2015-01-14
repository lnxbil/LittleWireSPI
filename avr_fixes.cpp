#include <time.h>
time_t start = time(0);


unsigned long millis()
{
    return 1000 * difftime( time(0), start);
}

unsigned long micros()
{
    return 1000 * 1000 * difftime( time(0), start);
}

