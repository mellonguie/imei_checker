### Global variables ###
DEBUG ?= 0
CC    ?= gcc

ifeq ($(DEBUG), 1)
    CFLAGS ?= -W -Wall -ansi -pedantic -g -O0 -D_DEFAULT_SOURCE -DDEBUG
else
    CFLAGS ?= -W -Wall -ansi -pedantic -D_DEFAULT_SOURCE
endif

APP = imei_imeisv_checking

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

### Rules to build target ###
all: $(APP)
ifeq ($(DEBUG), 1)
	@echo "===== Compilation in debug mode ====="
else
	@echo "===== Compilation in release mode ====="
endif

$(APP): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

### Program cleaning ###
.PHONY: clean

clean:
	rm -f $(APP) $(OBJ)

