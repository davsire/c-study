TARGET_SERVER = server
TARGET_CLIENT = client
SRC_SERVER = src/server.c src/protocolo/protocolo.c
SRC_CLIENT = src/client.c src/protocolo/protocolo.c
CC = gcc

server: $(SRC_SERVER)
	$(CC) $(SRC_SERVER) -o $(TARGET_SERVER)

client: $(SRC_CLIENT)
	$(CC) $(SRC_CLIENT) -o $(TARGET_CLIENT)

clean:
	rm $(TARGET_SERVER) $(TARGET_CLIENT)
