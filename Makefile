###############################################################################
# Makefile pra construir la biblioteca libgba                                 #
###############################################################################

# Cadena de desarrollo
TARGET      = arm-gba-elf
TOOLCHAIN   = /home/jesus/ae/$(TARGET)/bin
AR          = $(TOOLCHAIN)/$(TARGET)-ar
AS          = $(TOOLCHAIN)/$(TARGET)-as
CC          = $(TOOLCHAIN)/$(TARGET)-gcc


# Flags
INCDIR      = -I ../include
ASFLAGS     = $(INCDIR) -mcpu=arm7tdmi -mfpu=softfpa -gstabs
CFLAGS      = $(INCDIR) -g -Wall -mcpu=arm7tdmi -c
ARFLAGS     = -crs

LIB         = libgba.a
OBJS        = gba_video.o gba_bg.o gba_draw.o gba_keypad.o gba_dma.o gba_irq.o gba_timer.o gba_bios.o gba_sound.o gba_sprite.o gba_fp.o gba_rand.o

# Construcción
all : $(LIB)($(OBJS))

$(LIB)(%) : %
	$(AR) $(ARFLAGS) $(LIB) $<

%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(LIB)
	rm -f $(OBJS)
	rm -f *~
