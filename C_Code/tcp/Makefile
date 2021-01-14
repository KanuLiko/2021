all:server client
client:client.o
	gcc -o client client.c 
server:server.o 
	gcc -o server server.c 
clean:
	rm -f server client *.o
