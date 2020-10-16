CC = gcc
CFLAGS = -Wall -Wextra
OBJ = http-client

all:
	$(CC) $(CFLAGS) main.c params.c http.c -o $(OBJ)
exec:
	./$(OBJ)
clean:
	rm -rf *.o
	rm -rf $(OBJ)
