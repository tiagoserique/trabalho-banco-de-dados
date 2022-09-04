CC = g++
FLAGS = -Wall  
objects = main.o utils.o graph.o


all: compila


compila: $(objects)
	g++ $(objects) $(FLAGS) -o escalona


main.o: main.*
	g++ -c $(FLAGS) main.cpp


utils.o: utils.*
	g++ -c $(FLAGS) utils.cpp


graph.o: graph.*
	g++ -c $(FLAGS) graph.cpp


clean:
	rm *.o


purge: clean
	rm escalona

	