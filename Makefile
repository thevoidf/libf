CC = gcc
OUT = app

SRC = $(shell find src -name '*.c')
SRC += $(shell find deps -name '*.c')

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall
CFLAGS += -Ideps
# glib
CFLAGS += -I/usr/include/glib-2.0
CFLAGS += -I/usr/lib/glib-2.0/include

LDFLAGS += -Ldeps
LDFLAGS += -Ldeps/glfw
LDFLAGS += -ldl
LDFLAGS += -lX11
LDFLAGS += -lpthread
LDFLAGS += -lm
LDFLAGS += -lglfw3
# glib
LDFLAGS += -lglib-2.0

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-find . -type f -name '*.o' -delete
	-rm $(OUT)
