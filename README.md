# Sirocco

A easy to use C++ REST server. A personal project to learn C++ and improve my knowledge of the Internet. Feel free to fork it and have fun from scratch :)

## Files

- **`main`**: The example application to test the library.
- **`actions`**: The callbacks for the server endpoints.
- **`sirocco`**: The server itself.
- **`request`**: Module to handle the client's request.
- **`response`**: Module to handle the server's response.
- **`comm`**: Communication module that stores a request and a response.
- **`http`**: The HTTP tool.
- **`json`**: The JSON tool.
- **`utils`**: Functions to help around.

## Running the Example

The project lives in `src/server` and has a `main.cpp` file as test bench for the library.

All the processes are controlled using `make`. The `Makefile` describe all of them.

- Build the project: `make sirocco`.
- Run the project: `make start`.

## Testing the Server

To test the server, there is a `test.http` file that can be run using the VSCode extension [REST Client](https://marketplace.visualstudio.com/items?itemName=humao.rest-client).

## Documentation

The documentation has been created as a GitHub page. The project is written using [Svelte](https://svelte.dev/), and lives in `src/www`.

### Development

- `cd src/www`.
- `npm install`.
- `npm run dev`.
