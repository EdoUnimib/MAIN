main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp set.hpp
	g++ -c main.cpp -o main.o

.PHONY: clean
clean: 
	rm *.o *.exe

.PHONY: doc
doc: 
	doxygen