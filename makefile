
FLAGS = -Wall  
objects = main.o utils.o graph.o linked_list.o


all: compila


compila: $(objects)
	g++ $(objects) $(FLAGS) -o escalona


main.o: main.*
	g++ -c $(FLAGS) main.c


utils.o: utils.*
	g++ -c $(FLAGS) utils.c


graph.o: graph.*
	g++ -c $(FLAGS) graph.c


linked_list.o: linked_list.*
	g++ -c $(FLAGS) linked_list.c


clean:
	rm *.o


purge: clean
	rm escalona

	