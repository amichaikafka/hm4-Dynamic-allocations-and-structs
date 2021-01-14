CC=gcc
FLAGS=-Wall -g
OBGECT=frequency.c

all: frequency

frequency: $(OBGECT)
	$(CC) $(FLAGS) -o frequency $(OBGECT)

PHONY: clean all

clean:
	rm -f *.o  frequency 