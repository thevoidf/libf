CC = gcc
OUT = app

SRC = $(shell find src -name '*.c')
SRC += $(shell find deps -name '*.c')

OBJ = ${SRC:.c=.o}
# OBJ = $(patsubst src/%.c, src/%.o, $(SRC))
# OBJ = $(patsubst deps/%.c, deps/%.o, $(SRC))

CFLAGS = -Wall
CFLAGS += -Ideps
CFLAGS += -Ldeps
CFLAGS += `pkg-config --static --libs glfw3`

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# $(OBJ): src/%.o: src/%.c
# 	$(CC) $< -c -o $@ $(CFLAGS)

# OBJS = $(OBJ)
# OBJS += $(OBJC)

clean:
	-find . -type f -name '*.o' -delete
