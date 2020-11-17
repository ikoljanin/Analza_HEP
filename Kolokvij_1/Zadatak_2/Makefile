CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Zadatak_2.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

Z2: Z2.o Zadatak_2.o
	$(CC) $(LDFLAGS) -o Z2 Z2.o Zadatak_2.o

clean:
	rm -rf *.o Z2
