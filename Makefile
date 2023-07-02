CC ?= gcc
CFLAGS := -std=c99 -pedantic -O0 -Wall -Wextra -Wshadow -Werror
COBJFLAGS := $(CFLAGS) -c

SRCDIR := ./src
OBJDIR := ./obj
OUTDIR := ./bin

TARGET_NAME := tick-tock
TARGET := $(OUTDIR)/$(TARGET_NAME)

SRC := $(foreach x, $(SRCDIR), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

CLEAN_LIST := $(OBJ) $(TARGET)
PREFIX ?= /usr/local/bin


default: makedir all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $< $(COBJFLAGS)


.PHONY: makedir
makedir:
	@mkdir -p $(OUTDIR) $(SRCDIR) $(OBJDIR)

.PHONY: install
install:
	chmod 755 $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/

.PHONY: uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET_NAME)

.PHONY: clean
clean:
	@rm -f $(CLEAN_LIST)
