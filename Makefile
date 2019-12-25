CC = gcc
LIB = liblowg.a
SRC = $(shell find src -name '*.c')
SRC += $(shell find deps -name '*.c')
OBJ = ${SRC:.c=.o}

CFLAGS = -Wall
CFLAGS += -Ideps
CFLAGS += -I/usr/include/glib-2.0
CFLAGS += -I/usr/lib/glib-2.0/include

LDFLAGS = -Ldeps
LDFLAGS += -Ldeps/glfw
LDFLAGS += -ldl
LDFLAGS += -lX11
LDFLAGS += -lpthread
LDFLAGS += -lm
LDFLAGS += -lglfw3
LDFLAGS += -lglib-2.0

all: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

SRC_TEST = $(shell find test -name '*.c')
BIN_TEST = ${SRC_TEST:.c=}

CFLAGS += -Isrc
LDFLAGS += -L.
LDFLAGS += -llowg

test: $(BIN_TEST)

$(BIN_TEST): $(SRC_TEST)
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

lib:
	@echo "making lib"
	@$(foreach obj,$(OBJ),ar -cvq $(LIB) $(obj);)

clean:
	-find . -type f -name '*.o' -delete
	-rm -f $(LIB) $(BIN_TEST)

.PHONY: test lib clean
