# Sirocco

A easy to use C++ REST server. A personal project to learn C++ and improve my knowledge of the Internet. Feel free to fork it and have fun from scratch :)

## Files

- **`main`**: The example application to test the library.
- **`actions`**: The callbacks for the server endpoints.
- **`sirocco`**: The server library.
- **`response`**: The response tool to answer the request.
- **`http`**: The HTTP tool.
- **`json`**: The JSON tool.

## Running the Example

The project lives in `src/server` and has a `main.cpp` file as test bench for the library.

All the processes are controlled using `make`. The `Makefile` describe all of them.

- Build the project: `make`.
- Run the project: `make start`.

## Testing the Server

To test the server, there is a `test.http` file that can be run using the VSCode extension [REST Client](https://marketplace.visualstudio.com/items?itemName=humao.rest-client).

## Documentation

The documentation has been created as a GitHub page. The project is written using [Svelte](https://svelte.dev/), and lives in `src/www`.

### Development

- `cd src/www`.
- `npm install`.
- `npm run dev`.
