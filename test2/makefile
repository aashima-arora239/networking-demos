CC = gcc
BIN = ./../bin/
SRC = ./../src/
INCLUDE = -I./../include 
HEADER = ./../include/
OBJ = ./../obj/

all : $(BIN)server $(BIN)client

$(BIN)server: $(OBJ)s.o $(OBJ)functions.o
	$(CC) -g -Wall $(OBJ)s.o $(OBJ)functions.o -o server -lpthread
	mv server $(BIN)

$(BIN)client: $(OBJ)client.o $(OBJ)functions.o
	$(CC) -g -Wall $(OBJ)client.o $(OBJ)functions.o -o client
	mv client $(BIN)

$(OBJ)s.o: $(SRC)s.c $(HEADER)header.h
	$(CC) -c -g -Wall $(SRC)s.c $(INCLUDE)
	mv s.o $(OBJ)

$(OBJ)client.o: $(SRC)client.c $(HEADER)header.h
	$(CC) -c -g -Wall $(SRC)client.c $(INCLUDE)
	mv client.o $(OBJ)

$(OBJ)functions.o: $(SRC)functions.c $(HEADER)header.h
	$(CC) -c -g -Wall $(SRC)functions.c $(INCLUDE)
	mv functions.o $(OBJ)

clean:
	rm $(OBJ)*.o $(BIN)server $(BIN)client
