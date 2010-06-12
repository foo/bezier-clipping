FLAGS=-Wall -std=c99 -pedantic
OBJ=bezier.o graph.o quadclip.o casteljau.o reduction.o samples.o utils.o roots.o gui.o interval.o

bezier:
	gcc $(FLAGS) -c bezier.c

samples:
	gcc $(FLAGS) -c samples.c

graph: bezier casteljau
	gcc $(FLAGS) -c graph.c

casteljau: bezier
	gcc $(FLAGS) -c casteljau.c

quadclip: bezier reduction roots interval casteljau
	gcc $(FLAGS) -c quadclip.c

reduction: bezier utils
	gcc $(FLAGS) -c reduction.c

utils:
	gcc $(FLAGS) -c utils.c

interval:
	gcc $(FLAGS) -c interval.c

roots: bezier
	gcc $(FLAGS) -c roots.c

gui: graph reduction quadclip samples interval
	gcc $(FLAGS) -c gui.c

init: gui
	gcc $(FLAGS) init.c $(OBJ) -lglut -lpng -o lpp.e

all: init
clear:
	rm *.o *.e