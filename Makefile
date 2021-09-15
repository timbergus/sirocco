CC=clang++
CFLAGS=-std=c++17 -Werror -Wall -Wextra

TARGET=sirocco
ROOT=src/server
LIBRARY=$(ROOT)/library
BIN=$(ROOT)/bin

OBJS=	$(BIN)/comm.o		\
		$(BIN)/utils.o		\
		$(BIN)/json.o		\
		$(BIN)/http.o		\
		$(BIN)/response.o	\
		$(BIN)/request.o	\
		$(BIN)/sirocco.o	\
		$(BIN)/main.o

$(BIN)/%.o: $(LIBRARY)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(BIN)/%.o: $(ROOT)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	$(BIN)/sirocco

.PHONY: clean

clean:
	rm -r $(BIN)
