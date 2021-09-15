CC=clang++
CFLAGS=-std=c++17 -Werror -Wall -Wextra

APP=sirocco
SERVER=src/server
LIBRARY=$(SERVER)/library
BIN=$(SERVER)/bin

comm.o: $(LIBRARY)/comm.cpp $(LIBRARY)/comm.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/comm.cpp -o $(BIN)/comm.o

utils.o: $(LIBRARY)/utils.cpp $(LIBRARY)/utils.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/utils.cpp -o $(BIN)/utils.o

json.o: $(LIBRARY)/json.cpp $(LIBRARY)/json.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/json.cpp -o $(BIN)/json.o

http.o: $(LIBRARY)/http.cpp $(LIBRARY)/http.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/http.cpp -o $(BIN)/http.o

response.o: $(LIBRARY)/response.cpp $(LIBRARY)/response.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/response.cpp -o $(BIN)/response.o

sirocco.o: $(LIBRARY)/sirocco.cpp $(LIBRARY)/sirocco.h
	$(CC) $(CFLAGS) -c $(LIBRARY)/sirocco.cpp -o $(BIN)/sirocco.o

main.o: $(SERVER)/main.cpp $(SERVER)/actions.h
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c $(SERVER)/main.cpp -o $(BIN)/main.o

$(APP): main.o sirocco.o response.o http.o json.o utils.o comm.o
	$(CC) $(CFLAGS) $(BIN)/main.o $(BIN)/sirocco.o $(BIN)/response.o $(BIN)/http.o $(BIN)/json.o $(BIN)/utils.o $(BIN)/comm.o -o $(BIN)/$(APP)

start:
	$(BIN)/sirocco

.PHONY: clean

clean:
	rm -r $(BIN)
