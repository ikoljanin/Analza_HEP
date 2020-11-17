CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS =PDFGenerator.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

pdf_generator: pdf_generator.o PDFGenerator.o
	$(CC) $(LDFLAGS) -o pdf_generator pdf_generator.o PDFGenerator.o

clean:
	rm -rf *.o pdf_generator
