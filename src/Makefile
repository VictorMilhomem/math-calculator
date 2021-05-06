calculator: main.o standard_devi.o help.o scalarprod.o regression.o runMenu.o
	gcc main.o standard_devi.o regression.o help.o scalarprod.o runMenu.o -o calculator -lm

main.o: main.c calc.h
	gcc -c main.c

runMenu.o: runMenu.c calc.h
	gcc -c runMenu.c

help.o: help.c
	gcc -c help.c

standard_devi.o: standard_devi.c
	gcc -c standard_devi.c -lm

regression.o: regression.c
	gcc -c regression.c -lm

scalarprod.o: scalarprod.c
	gcc -c scalarprod.c

clean:
	rm *.o calculator