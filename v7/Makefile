CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Analysis.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

Analyze: Analyze.o Analysis.o
	$(CC) $(LDFLAGS) -o Analyze Analyze.o Analysis.o

clean:
	rm -rf *.o Analyze
