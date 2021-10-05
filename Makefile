CC=clang++

TARGET=sirocco

ROOT=src/server
APP=${ROOT}/app
INCLUDE=$(ROOT)/include

ifeq ($(OS),Windows_NT) # is Windows_NT on XP, 2000, 7, Vista, 10...
	IFLAGS=-I $(INCLUDE)
	BIN=src\server\bin
else
	IFLAGS=-I $(INCLUDE) -I /usr/local/include
	LFLAGS=-L /usr/local/lib -lfmt
	BIN=$(ROOT)/bin
endif

CFLAGS=-std=c++2a -Werror -Wall -Wextra

OBJS=$(BIN)/main.o

$(BIN)/%.o: $(INCLUDE)/%.cpp
ifeq ($(OS),Windows_NT)
	@mkdir $(BIN)
else
	@mkdir -p $(BIN)
endif
	$(CC) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(BIN)/%.o: $(APP)/%.cpp
ifeq ($(OS),Windows_NT)
	@mkdir $(BIN)
else
	@mkdir -p $(BIN)
endif
	$(CC) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

-include $(BIN)/*.d

start:
	$(BIN)/$(TARGET)

.PHONY: clean

clean:
ifeq ($(OS),Windows_NT)
	@rmdir /S/Q $(BIN)
else
	@rm -r $(BIN)
endif
