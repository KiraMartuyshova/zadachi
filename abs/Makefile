all: absolute

absolute: main.o a_abs.o 
	g++ main.o a_abs.o -o absolute

test3.o: main.cpp
	g++ -c main.cpp

a_abs.o: a_abs.cpp
	g++ -c a_abs.cpp a.h

clean:
	rm -rf *.o absolute