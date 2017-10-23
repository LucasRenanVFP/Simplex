exe: tools.o main.o simplex.o solver.o
	g++ -std=c++11 tools.o main.o simplex.o solver.o -o exe
main.o: main.cpp tools.h simplex.h solver.h
	g++ -std=c++11 -g -c main.cpp
tools.o: tools.h tools.cpp
	g++ -std=c++11 -g -c tools.cpp
simplex.o: simplex.h tools.h simplex.cpp
	g++ -std=c++11 -g -c simplex.cpp
solver.o: solver.h simplex.h tools.h solver.cpp
	g++ -std=c++11 -g -c solver.cpp

clean:
	rm *.o *.gch
	rm mont
