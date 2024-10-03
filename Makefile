CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -Iinclude

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

EXEC = nue

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXEC) $(OBJECTS)

.PHONY: all clean
