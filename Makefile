TARGET = arm-none-eabi
AR           = $(TOOLCHAINPATH)/bin/$(TARGET)-ar
AS           = $(TOOLCHAINPATH)/bin/$(TARGET)-as
CC           = $(TOOLCHAINPATH)/bin/$(TARGET)-gcc

INCDIR      = -I include
ASFLAGS     = $(INCDIR) -mcpu=arm7tdmi -mfpu=softfpa -gstabs
CFLAGS      = $(INCDIR) -g -Wall -mcpu=arm7tdmi -c
ARFLAGS     = -crs

LIB         = libgba.a
OBJS        = gba_video.o gba_bg.o gba_draw.o gba_keypad.o gba_dma.o gba_irq.o gba_timer.o gba_bios.o gba_sound.o gba_sprite.o gba_fp.o gba_rand.o

all : checkpath $(LIB)($(OBJS))

checkpath:
ifndef TOOLCHAINPATH
	@echo
	@echo No toolchain path defined.
	@echo
	@echo Please, use make TOOLCHAINPATH=path/to/toolchain
	@echo
	@echo Example: make TOOLCHAINPATH=~/Download/gcc-arm-none-eabi-4_7-2013q1/
	@echo
	@echo Get a suitable toolchain from https://launchpad.net/gcc-arm-embedded
	@echo
	@exit 1
endif

$(LIB)(%) : %
	$(AR) $(ARFLAGS) $(LIB) $<

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(LIB)
	rm -f $(OBJS)
