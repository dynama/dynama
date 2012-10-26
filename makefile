CC=gcc
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
TAGS = -I. -lpcap -lsqlite3


zombie_watch: $(OBJECTS)
	$(CC) -o zombie_watch $(OBJECTS) $(TAGS)

%.o: %.c
	$(CC) -c $^

.PHONY: clean

clean:
	-rm -f *.o *~ core *.core 

