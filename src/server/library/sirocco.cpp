#include "sirocco.h"

sirocco::Sirocco::Sirocco(int port)
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

sirocco::Sirocco::~Sirocco()
{
  close_connections();
}

void sirocco::Sirocco::listening()
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

  char request[REQUEST_MAX_LENGTH];

  int bytes_read = read(connection, request, sizeof(request));

  parse_request(request);

  std::cout << "Bytes read: " << bytes_read << std::endl;
  std::cout << "The message was: " << request << std::endl;

  // Launchign callbacks.

  handlers[tokens[0] + "_" + tokens[1]](connection);

  std::cout << "Done!" << std::endl;
}

void sirocco::Sirocco::parse_request(char *response)
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

void sirocco::Sirocco::get(std::string url, std::function<void(int)> callback)
{
  handlers["GET_" + url] = callback;
}

void sirocco::Sirocco::post(std::string url, std::function<void(int)> callback)
{
  handlers["POST_" + url] = callback;
}

void sirocco::Sirocco::put(std::string url, std::function<void(int)> callback)
{
  handlers["PUT_" + url] = callback;
}

void sirocco::Sirocco::del(std::string url, std::function<void(int)> callback)
{
  handlers["DELETE_" + url] = callback;
}

void sirocco::Sirocco::close_connections()
{
  close(connection);
  close(socket_fd);
  std::cout << "Closing socket" << std::endl;
}
