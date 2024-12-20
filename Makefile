# Makefile

CC = g++

main.exe : main.o
	g++ -g main.o -o main.exe

main.o : main.cpp pkeScheme.h
	g++ -c main.cpp pkeScheme.h

clean:
	@echo cleaning project...
	-del -f main.exe *.o *.gch
	@echo clean completed