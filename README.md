# LittleWireSPI

This is a small wrapper library for using code formely designed for Arduino to run on an ordinary PC-like machine with [libusb](http://www.libusb.org/), especially the excellent family of libraries:

* [TMRh20's enhanced RF24 Library](https://github.com/TMRh20/RF24)
* [TMRh20's enhanced RF24Network Library](https://github.com/TMRh20/RF24Network)

by using Ihsan Kehribar's [LittleWire](http://littlewire.cc/) hardware/software projects which allows to call SPI on hardware level via a small device over USB from a libusb-capable operating system.

This approach needs approximately 1ms per SPI call, so it is not very fast (around 1 kHz), but it works.


## Installation

Currently tested on Linux and MacOS:

* Edit ```Makefile``` to match your install prefix ```PREFIX``` if neccessary
* run ```make install``` (maybe using ```sudo``` if neccessary)

I can strongly suggest to use a fixed path for all RF24-related stuff like I did in using

```
/opt/LittleWirePrefix
```

for all projects to get everything in one place without using ```sudo``` or running as ```root```. The only thing you need to do is creating and chowning the directory as ```root``` to your default user and stick with it.

### Packages

There is also a prebuilt Debian Wheezy (amd64) package available:

RELEASE TBD
