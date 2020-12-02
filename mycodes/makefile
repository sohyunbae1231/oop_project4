main : Object.o DDGame.o MainForTest.o
	g++ Object.o DDGame.o MainForTest.o -o main

MainForTest.o : DDGame.h MainForTest.cpp
	g++ -c MainForTest.cpp

DDGame.o : Object.h DDGame.h DDGame.cpp
	g++ -c DDGame.cpp

Object.o : Object.h Object.cpp
	g++ -c Object.cpp