# Clang as the compiler.

CXX=clang++

# The project name as the target.

TARGET=sirocco

# Paths to app and include directories from the root path.
# The folder structure is:
#
# bin
# src
#  | app
#  | include

ROOT=src/server
APP=$(ROOT)/app
INCLUDE=$(ROOT)/include
BIN=bin

# We need to choose between Windows and Mac.

ifeq ($(OS),Windows_NT) # is Windows_NT on XP, 2000, 7, Vista, 10...
	IFLAGS=-I $(INCLUDE)
else
	IFLAGS=-I $(INCLUDE) -I /usr/local/include
	LFLAGS=-L /usr/local/lib -lfmt
endif

# Always the latest and greatest of the C++ standard.

CFLAGS=-std=c++2a -Werror -Wall -Wextra

# We need a .o for every .cpp file.

OBJS=$(BIN)/main.o

# One process per folder.

# INCLUDE
$(BIN)/%.o: $(INCLUDE)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BIN) mkdir $(BIN)
else
	@mkdir -p $(BIN)
endif
	$(CXX) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

# APP
$(BIN)/%.o: $(APP)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BIN) mkdir $(BIN)
else
	@mkdir -p $(BIN)
endif
	$(CXX) $(CFLAGS) $(IFLAGS) -c -MD $< -o $@

# And we link all the objects files together including the libraries.

$(TARGET): $(OBJS)
	@$(CXX) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(BIN)/$(TARGET)

# We include the headers definitions.

-include $(BIN)/*.d

start:
	$(BIN)/$(TARGET)

# Here we add a phony rule to make the Makefile happy.

.PHONY: clean

clean:
ifeq ($(OS),Windows_NT)
	@rmdir /S/Q $(BIN)
else
	@rm -r $(BIN)
endif
