CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Lifetime.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

life: life.o Lifetime.o
	$(CC) $(LDFLAGS) -o life life.o Lifetime.o

clean:
	rm -rf *.o life
