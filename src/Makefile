exec = calculator
sources = $(wildcard *.c)
objects = $(sources:.c=.o)
flags = -lm


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c %.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./calculator /usr/local/bin/calculator

clean:
	-rm *.o calculator

