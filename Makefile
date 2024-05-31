CC ?= gcc
CFLAGS := -std=c99 -pedantic -Wall -Wextra $(shell pkg-config --cflags libnotify)
LIBS := $(shell pkg-config --libs libnotify) $(shell pkg-config --libs libprocps)

PREFIX ?= /usr/local
TARGET_NAME := tick-tock
TARGET := build/$(TARGET_NAME)


all: $(TARGET)

$(TARGET): src/main.c
	mkdir -p build
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

.PHONY: install
install:
	chmod 755 $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp -f $(TARGET) $(PREFIX)/bin/

.PHONY: uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET_NAME)
