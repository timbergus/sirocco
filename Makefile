all:
	clang++ -std=c++2a src/server/main.cpp -o build/main

start:
	./build/main
