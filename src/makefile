
FLAGS=-Wall -std=c99 -pedantic
OBJ=../bin/bezier.o ../bin/graph.o ../bin/quadclip.o ../bin/casteljau.o ../bin/reduction.o ../bin/samples.o ../bin/utils.o ../bin/power.o ../bin/interval.o

power:
	gcc $(FLAGS) -c power.c -o ../bin/power.o

bezier: power
	gcc $(FLAGS) -c bezier.c -o ../bin/bezier.o

samples:
	gcc $(FLAGS) -c samples.c -o ../bin/samples.o

graph: bezier casteljau
	gcc $(FLAGS) -c graph.c -o ../bin/graph.o

casteljau: bezier
	gcc $(FLAGS) -c casteljau.c -o ../bin/casteljau.o

quadclip: bezier reduction interval casteljau
	gcc $(FLAGS) -c quadclip.c -o ../bin/quadclip.o

reduction: bezier utils
	gcc $(FLAGS) -c reduction.c -o ../bin/reduction.o

utils:
	gcc $(FLAGS) -c utils.c -o ../bin/utils.o

interval:
	gcc $(FLAGS) -c interval.c -o ../bin/interval.o

main: graph reduction quadclip samples interval
	gcc $(FLAGS) main.c $(OBJ) -lm -o ../bin/lpp.e

all: main
clear:
	rm ../bin/*