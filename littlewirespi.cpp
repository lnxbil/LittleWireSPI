#include "littlewirespi.h"

extern "C" {
#include <littleWire.h>
#include <littleWire_util.h>
}

#define perrorf(...) fprintf(stderr, __VA_ARGS__)

usb_dev_handle *lw = NULL;
unsigned long number_of_spi_calls = 0;

void connect()
{
    unsigned char version;
    int total_lwCount;
    int i;

    total_lwCount = littlewire_search();

    if(total_lwCount == 1)
    {
        printf("----------------------------------------------------------\n");
        printf("> 1 Little Wire device is found with serialNumber: %d\n",lwResults[0].serialNumber);
        printf("----------------------------------------------------------\n");
    }
    else if(total_lwCount > 1)
    {
        printf("----------------------------------------------------------\n");
        printf("> %d Little Wire devices are found\n",total_lwCount);
        printf("----------------------------------------------------------\n");
        printf("> #id - serialNumber\n");
        for(i=0;i<total_lwCount;i++)
        {
            printf(">  %2d - %3d\n",i,lwResults[i].serialNumber);
        }
        printf("----------------------------------------------------------\n");
    }
    else if(total_lwCount == 0)
    {
        printf("----------------------------------------------------------\n");
        printf("> Little Wire could not be found!\n");
        printf("----------------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }

    /* Connects to the first littleWire device the computer can find. */
    // lw = littleWire_connect();

    /* Connects to the spesific littleWire device by array id. */
    lw = littlewire_connect_byID(0);

    /* Connects to the spesific littleWire with a given serial number. */
    /* If multiple devices have the same serial number, it connects to the last one it finds */
    // lw = littlewire_connect_bySerialNum(126);

    if(lw == NULL){
        printf("> Little Wire connection problem!\n");
        exit(EXIT_FAILURE);
    }

    version = readFirmwareVersion(lw);
    printf("> Little Wire firmware version: %d.%d\n",((version & 0xF0)>>4),(version&0x0F));
    if(version < 0x12)
    {
        printf("> This example requires the new 1.2 version firmware. Please update soon.\n");
        exit(EXIT_FAILURE);
    }
}

void digitalWrite(unsigned char pin, unsigned char state)
{
    digitalWrite(lw, pin, state);
}

void pinMode(unsigned char pin, unsigned char direction)
{
    pinMode(lw, pin, direction);
}

// each call increases the number_of_spi_calls
byte LittleWireSPI::transfer(byte _data)
{
    byte returnVal = 0;

    spi_sendMessage(
            lw,
            &_data,
            &returnVal,
            1,
            MANUAL_CS
    );

    if (lwStatus < 0)
    {
        printf("> lwStatus: %d\n", lwStatus);
        exit(EXIT_FAILURE);
    }

    number_of_spi_calls++;

    return returnVal;
}

void LittleWireSPI::begin()
{
    perrorf("Initializing SPI\n");
    spi_init(lw);
    spi_updateDelay(lw,1); 
}


void LittleWireSPI::end()
{}

unsigned int getSPICalls()
{
    return number_of_spi_calls;
}
