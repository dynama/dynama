HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))


zombie_watch: $(OBJECTS)
	gcc -o zombie_watch $(OBJECTS) -I. -lpcap -lsqlite3

sniffer.o: sniffer.c
	gcc -c sniffer.c

parser.o: parser.c
	gcc -c parser.c

database.o: database.c
	gcc -c database.c 

clean:
	-rm -f *.o
	-rm -f sniffer
	-rm -f parser	




