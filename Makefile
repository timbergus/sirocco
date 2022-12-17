BUILD=build

init:
	conan install . -if $(BUILD) && cmake -B $(BUILD)

build_project:
	cmake --build $(BUILD)

start:
	./$(BUILD)/sirocco

clean:
	rm -rf $(BUILD)
