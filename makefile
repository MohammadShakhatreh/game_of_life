LIBS=-lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

build: main.o
	g++ main.o -o sfml-app $(LIBS)

clean:
	rm *.o
