CC=g++-11
CFLAGS=-std=c++20 -Werror -Wall -Wextra -I $(LIBRARY)/include

TARGET=sirocco
ROOT=src/server
APP=${ROOT}/app
LIBRARY=$(ROOT)/library
BIN=$(ROOT)/bin

OBJS=	$(BIN)/main.o		\
		$(BIN)/sirocco.o	\
		$(BIN)/request.o	\
		$(BIN)/response.o	\
		$(BIN)/comm.o		\
		$(BIN)/http.o		\
		$(BIN)/json.o		\
		$(BIN)/utils.o

$(BIN)/%.o: $(LIBRARY)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(BIN)/%.o: $(APP)/%.cpp
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	$(BIN)/$(TARGET)

.PHONY: clean

clean:
	rm -r $(BIN)
