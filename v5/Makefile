CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

Analyze: Analyze.o Analyzer.o
	$(CC) $(LDFLAGS) -o Analyze Analyze.o Analyzer.o

clean:
	rm -rf *.o Analyze
