# Sirocco

A easy to use C++ REST server. A personal project to learn C++ and improve my knowledge of the Internet. Feel free to fork it and have fun from scratch 🙂

## Files

- **`main`**: The example application to test the library.
- **`actions`**: The callbacks for the server endpoints.
- **`server`**: The server itself.
- **`request`**: Module to handle the client's request.
- **`response`**: Module to handle the server's response.
- **`comm`**: Communication module that stores a request and a response.
- **`http`**: The HTTP tool.
- **`json`**: The JSON tool.
- **`utils`**: Functions to help around.

## Running the Example

The project lives in `src/server` and has a `main.cpp` file as test bench for the library.

All the processes are controlled using `make`. The `Makefile` describe all of them.

- Cleans the project: `make clean`.
- Inits the project: `make init`.
- Builds the project: `make sirocco`.
- Runs the project: `make start`.
- Test the project: `make test`.

## Testing the Server

To test the server, there is a `test.http` file that can be run using the VSCode extension [REST Client](https://marketplace.visualstudio.com/items?itemName=humao.rest-client).

> Right now this is not working due to this [error](https://stackoverflow.com/questions/63037406/postman-error-parse-error-invalid-header-value-char) that I'm trying to fix, but using a browser and opening [localhost](http://localhost:3000) should show you a web page. Also, it works with `curl` and the console version of `httpie`. It seems to be failing with programs like Postman.

## Documentation

The documentation has been created as a GitHub page. The project is written using [React](https://reactjs.org/), and lives in `src/www`.

### Development

- `cd src/www`.
- `yarn`.
- `yarn dev`.

And after your changes are production ready.

- `yarn build`.

The result of the build will be stored in the `docs` folder and published by GitHub.
