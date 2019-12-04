all: echo_client

echo_client: main.o echo_client.o
	g++ -std=gnu++11 -g -o echo_client main.o echo_client.o -lpthread

echo_client.o: echo_client.cpp echo_client.h
	g++ -std=gnu++11 -g -c -o echo_client.o echo_client.cpp

main.o: main.cpp
	g++ -std=gnu++11 -g -c -o main.o main.cpp

clean:
	rm -f echo_client
	rm -f *.o

