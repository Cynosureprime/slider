CC      = gcc
CC_WIN  = x86_64-w64-mingw32-gcc
CC_FUZZ = afl-clang-lto

CFLAGS      = -Wall -O3
CFLAGS_WIN  = -Wall -O3 -D_WINDOWS
CFLAGS_FUZZ = -Wall -O3 -ggdb

all: slider slider.exe

clean:
	rm -f slider slider.exe slider.fuzz

fuzz: slider.fuzz

slider: main.c
	$(CC) $(CFLAGS) -o $@ $^

slider.exe: main.c
	$(CC_WIN) $(CFLAGS_WIN) -o $@ $^

slider.fuzz: main.c
	$(CC_FUZZ) $(CFGLAS_FUZZ) -o $@ $^
