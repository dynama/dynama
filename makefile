zombie_watch: sniffer.o parser.o
	gcc -o zombie_watch parser.o sniffer.o -I. -lpcap 

sniffer.o: sniffer.c
	gcc -c sniffer.c

parser.o: parser.c
	gcc -c parser.c

clean:
	-rm -f *.o
	-rm -f sniffer
	-rm -f parser	




