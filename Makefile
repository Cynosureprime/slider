VERSION=1.0

CC      ?= gcc
CC_WIN  ?= x86_64-w64-mingw32-gcc
CC_FUZZ ?= afl-clang-lto

CFLAGS_COMMON = -Wall -Wextra -O3
CFLAGS        = $(CFLAGS_COMMON) -s
CFLAGS_WIN    = $(CFLAGS) -D_WINDOWS
CFLAGS_FUZZ   = $(CFLAGS_COMMON) -ggdb

TMPDIR=/tmp/slider-$(VERSION)

all: slider

win: slider.exe

clean:
	rm -f slider slider.exe slider.fuzz slider$(VERSION).zip

fuzz: slider.fuzz

slider: main.c
	$(CC) $(CFLAGS) -o $@ $^

slider.exe: main.c
	$(CC_WIN) $(CFLAGS_WIN) -o $@ $^

slider.fuzz: main.c
	$(CC_FUZZ) $(CFLAGS_FUZZ) -o $@ $^

release: clean slider win
	mkdir -p $(TMPDIR)
	cp slider slider.exe $(TMPDIR)
	7z a slider-$(VERSION).zip $(TMPDIR)
