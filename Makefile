all:
	mkdir build && cd build && conan install .. && cd .. && cmake -B build && cmake --build build

start:
	./build/sirocco

clean:
	rm -rf build
