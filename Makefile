#############################################################################
#
# Makefile for LittleWireSPI
#
# License: GPL (General Public License)
# Author:  Andreas Steinel
# Date:    2015/01/05
#
# Description:
# ------------
# use make all and make install to install the library 
# You can change the install directory by editing the PREFIX line
#

PREFIX=/opt/LittleWirePrefix

LITTLEWIRE_PATH=external-littlewire/software
USBFLAGS = $(shell libusb-config --cflags)
USBLIBS = $(shell libusb-config --libs)


LIB=liblittlewire-spi
LIB_DIR=$(PREFIX)/lib

ifeq ($(shell uname), Linux)
	DYN_SUFFIX=so.1
	LINK_FORMAT=-shared -Wl,-soname,$@.$(DYN_SUFFIX)
#	DPKG_BUILD_FLAGS_PRESENT := $(shell dpkg-buildflags --version 2>/dev/null)
#ifdef DPKG_BUILD_FLAGS_PRESENT
#	@echo "dpkg-buildflags present, using it"
#	CPPFLAGS:=$(shell dpkg-buildflags --get CPPFLAGS)
#	CFLAGS:=$(shell dpkg-buildflags --get CFLAGS)
#	CXXFLAGS:=$(shell dpkg-buildflags --get CXXFLAGS)
#	LDFLAGS:=$(shell dpkg-buildflags --get LDFLAGS)
#endif
else ifeq ($(shell uname), Darwin)
	DYN_SUFFIX=dylib
	LINK_FORMAT=-shared -dynamiclib -install_name ${LIB_DIR}/${LIB}.${DYN_SUFFIX}
else
	$(shell echo "Unknown System, please fix Makefile!")
	$(shell false )
endif

LIBNAME=$(LIB).$(DYN_SUFFIX)

# Where to put the header files
HEADER_DIR=${PREFIX}/include/LittleWireSPI

# We need to behave like LINUX (in LittleWire terms)
CFLAGS+=-fPIC -I$(LITTLEWIRE_PATH)/library $(USBFLAGS) -DLINUX
CXXFLAGS+=-fPIC -I$(LITTLEWIRE_PATH)/library $(USBFLAGS) -DLINUX
LDFLAGS+=$(USBLIBS)

# make all
# reinstall the library after each recompilation
all: $(LIB)

avr_fixes.o: avr_fixes.cpp
	$(CC) ${CFLAGS} -c $^

littlewirespi.o: littlewirespi.cpp
	$(CXX) ${CXXFLAGS} -c $^

# Littlewire Library
# ----------------------------------------------------------------------
LWLIBS = littleWire littleWire_util littleWire_servo opendevice

library: $(LWLIBS)

%.o: external-littlewire/software/library/%.c
	$(CC) ${CFLAGS} -c $^

#$(LWLIBS):
#	$(CC) $(CFLAGS) -c external-littlewire/software/library/$@.c

# ----------------------------------------------------------------------
#
# Make the library
$(LIB): littlewirespi.o avr_fixes.o $(LWLIBS:%=%.o)
	$(CC) ${CFLAGS} ${LINK_FORMAT} -o ${LIBNAME} $^ ${LDFLAGS}
	
# clear build files
clean:
	rm -rf *.o ${LIB}.*

install: all install-libs install-headers

# Install the library to LIBPATH
install-libs: 
	@echo "[Installing Libs]"
	@if ( test ! -d $(LIB_DIR) ) ; then mkdir -p $(LIB_DIR) ; fi
	@install -m 0755 ${LIBNAME} ${LIB_DIR}

install-headers:
	@echo "[Installing Headers]"
	@if ( test ! -d ${HEADER_DIR} ) ; then mkdir -p ${HEADER_DIR} ; fi
	@install -m 0644 *.h ${HEADER_DIR}


# you need 'devscripts' package installed
deb:
	@rm -rf debian/liblittlewire-spi*
	@tar -jcf ../liblittlewirespi_1.0.orig.tar.bz2 ../LittleWireSPI
	@debuild -i -us -uc -b
