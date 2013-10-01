CC = gcc
CFLAGS = -Wall -D_REENTRANT
LDFLAGS = -lpthread

SRCS = $(wildcard *.c)
EXES = $(patsubst %.c, %, $(SRCS))

all: $(EXES)

clean:
	rm -f $(EXES)

