all: geometric

geometric: main.o geom.o 
	g++ main.o geom.o -o geometric

main.o: main.cpp
	g++ -c main.cpp

geom.o: geom.cpp
	g++ -c geom.cpp geom.h

clean:
	rm -rf *.o geometric