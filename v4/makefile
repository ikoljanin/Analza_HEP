CC=g++
CFLAGS=-I.
DEPS = Analyzer.h
CFLAGS=-I.$(shell root-config --cflags)
LDFLAGS= $(shell root-config --libs

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyze: analyze.o Analyzer.o
	$(CC) -o analyze analyze.o Analyzer.o
	$(LDFLAGS)

clean:
	rm -rf *.o analyze
