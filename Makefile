init:
	cd bin && conan install .. && cmake ..

build:
	cd bin && make

start:
	./bin/sirocco

clean:
	cd bin && rm -rf *
