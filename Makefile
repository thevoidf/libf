CC = gcc
LIB = liblowg.a
SRC = $(shell find src -name '*.c')
SRC += $(shell find deps -name '*.c')
OBJ = ${SRC:.c=.o}

OS=$(shell uname -s)

CFLAGS = -Wall
CFLAGS += -Ideps

LDFLAGS = -Ldeps

ifeq ($(OS),Linux)
LDFLAGS += -lX11
LDFLAGS += -Ldeps/glfw/linux
endif
ifeq ($(OS),Darwin)
LDFLAGS += -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon
LDFLAGS += -Ldeps/glfw/mac
endif
LDFLAGS += -lglfw3
LDFLAGS += -lpthread
LDFLAGS += -ldl
LDFLAGS += -lm

all: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

SRC_TEST = $(shell find test -name '*.c')
BIN_TEST = ${SRC_TEST:.c=}

CFLAGS += -Isrc
LDFLAGS += -L.
LDFLAGS += -llowg
LDFLAGS += -Ldeps/glfw
LDFLAGS += -lglfw3

test: $(BIN_TEST)

test/%: test/%.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

lib:
	@echo "making lib"
	@$(foreach obj,$(OBJ),ar -cvq $(LIB) $(obj);)

clean:
	-find . -type f -name '*.o' -delete
	-rm -f $(LIB) $(BIN_TEST)

.PHONY: test lib clean
