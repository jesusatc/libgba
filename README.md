libgba
======

libgba (A library to develop Game Boy Advance games).
Copyright (c) 2008-2009, Jesús González - https://github.com/jesusatc

In order to compile libgba:

1. Download the GNU Tools for ARM Embedded Processors from https://launchpad.net/gcc-arm-embedded

2. Extract the GNU Tools for ARM Embedded Processors somewhere.

3. Download libgba sourse.

4. Get into the libgba source directory and run:
            
            $ make TOOLCHAINPATH=path/to/toolchain

Example:

            $ make TOOLCHAINPATH=~/gcc-arm-none-eabi-4_7-2013q1/

This will compile the library itself, libgba.a.

For a complete GBA game example developed using libgba, check SpaceARMy - https://github.com/lquesada/SpaceARMy
