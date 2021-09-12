#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <functional>

class HTTPServer
{
private:
  int REQUEST_MAX_LENGTH = 1024;

  struct handler
  {
    std::string verb;
    std::string url;
    std::function<void(int)> callback;
  };

  std::vector<handler> handlers;

  int socket_fd;
  sockaddr_in sockaddr;
  int connection;
  std::vector<std::string> tokens;

  void close_connections();

public:
  HTTPServer(int);
  ~HTTPServer();

  void listening();
  void parse_request(char *);
  void get(std::string, std::function<void(int)>);
  void post(std::string, std::function<void(int)>);
  void put(std::string, std::function<void(int)>);
  void del(std::string, std::function<void(int)>);
};

HTTPServer::HTTPServer(int port)
{
  // First we need to define the socket. This is the file descriptor.

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  // This is a simply validation that the socket has been created.

  if (socket_fd == -1)
  {
    std::cout << "Error creating socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Now we need to bind the socket to a port. A sockaddr is a structure
  // that contains the address of the socket.

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
}

HTTPServer::~HTTPServer()
{
  close_connections();
}

void HTTPServer::listening()
{
  int listening = listen(socket_fd, 10);

  if (listening < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening on port " << sockaddr.sin_port << std::endl;

  // Now we need to accept the connection.

  unsigned long addrlen = sizeof(sockaddr);

  std::cout << "Waiting for connection..." << std::endl;

  connection = accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (connection < 0)
  {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Connected" << std::endl;

  // while (true)
  // {
  char request[REQUEST_MAX_LENGTH];

  int bytes_read = read(connection, request, sizeof(request));

  parse_request(request);

  std::cout << "Bytes read: " << bytes_read << std::endl;
  std::cout << "The message was: " << request << std::endl;

  // Launchign callbacks.

  handlers[0].callback(connection);

  std::cout << "Done!" << std::endl;
  // }
}

void HTTPServer::parse_request(char *response)
{
  char *token = strtok(response, " ");

  while (token != NULL)
  {
    tokens.push_back(token);
    token = strtok(NULL, " ");
  }

  std::cout << "The verb is: " << tokens[0] << std::endl;
  std::cout << "The URL is: " << tokens[1] << std::endl;
}

void HTTPServer::get(std::string url, std::function<void(int)> callback)
{
  handler h = {"GET", "/" + url, callback};
  handlers.push_back(h);
}

void HTTPServer::post(std::string url, std::function<void(int)> callback)
{
  handler h = {"POST", "/" + url, callback};
  handlers.push_back(h);
}

void HTTPServer::put(std::string url, std::function<void(int)> callback)
{
  handler h = {"PUT", "/" + url, callback};
  handlers.push_back(h);
}

void HTTPServer::del(std::string url, std::function<void(int)> callback)
{
  handler h = {"DELETE", "/" + url, callback};
  handlers.push_back(h);
}

void HTTPServer::close_connections()
{
  close(connection);
  close(socket_fd);
  std::cout << "Closing socket" << std::endl;
}

int main(int argc, char const *argv[])
{
  HTTPServer server(3000);

  server.get("/home", [](int connection)
             {
               std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>This is a POST!</h1>";
               send(connection, response.c_str(), response.size(), 0);
             });

  server.listening();

  return EXIT_SUCCESS;
}
