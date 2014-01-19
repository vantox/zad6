COMP = g++
CFLAGS = -Wall -std=c++11 -Wextra -pedantic

all: grubaryba_example

mojagrubaryba.o: mojagrubaryba.h mojagrubaryba.cc
	$(COMP) $(CFLAGS) mojagrubaryba.cc -c

grubaryba_example.o: grubaryba_example.cc
	$(COMP) $(CFLAGS) grubaryba_example.cc -c

grubaryba_example: grubaryba_example.o mojagrubaryba.o
	$(COMP) $(CFLAGS) grubaryba_example.o mojagrubaryba.o -o grubaryba_example

clean:
	rm -f grubaryba_example *~ *.o *.orig
