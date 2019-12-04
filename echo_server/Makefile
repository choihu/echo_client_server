all: echo_server

echo_server: main.o echo_server.o
	g++ -std=gnu++11 -g -o echo_server main.o echo_server.o -lpthread

echo_server.o: echo_server.cpp echo_server.h
	g++ -std=gnu++11 -g -c -o echo_server.o echo_server.cpp

main.o: main.cpp
	g++ -std=gnu++11 -g -c -o main.o main.cpp

clean:
	rm -f echo_server
	rm -f *.o

