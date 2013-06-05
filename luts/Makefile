# Flags
CFLAGS      = -g -Wall
LDFLAGS     = -lm

# Programa
EXE = print_luts
SOURCE = $(EXE).c
LUTS = luts.c

all : $(EXE)
	@echo "Writing luts to luts.c"
	@./$(EXE) > $(LUTS)

$(EXE) : $(SOURCE)
	@gcc $(CFLAGS) $(SOURCE) -o $(EXE) $(LDFLAGS)

clean:
	rm -f $(EXE) $(LUTS)
	rm -f *~

