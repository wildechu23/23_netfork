all: client server


client: basic_client.o networking.o
	gcc -o client basic_client.o networking.o

server: basic_server.o networking.o
	gcc -o server basic_server.o networking.o

basic_client.o: basic_client.c networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c networking.h
	gcc -c basic_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
