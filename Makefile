CLI = client
SER = server
SERVER = gcc server.c -o $(SER)
CLIENT = gcc client.c -o $(CLI)

all:
	$(CLIENT)
	$(SERVER)

client:
	$(CLIENT)

server:
	$(SERVER)

clean:
	rm $(CLI) $(SER)
