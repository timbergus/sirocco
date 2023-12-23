BUILD=build
PROJECT=sirocco

init:
	conan install . --output-folder=$(BUILD) --build=missing && cmake -B $(BUILD)

sirocco:
	cmake --build $(BUILD)

start:
	./$(BUILD)/$(PROJECT)

test:
	ctest --test-dir $(BUILD)

clean:
	rm -rf $(BUILD)
