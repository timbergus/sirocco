#include "sirocco.h"

Sirocco::Sirocco(int port)
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

Sirocco::~Sirocco()
{
  close_connections();
}

void Sirocco::listening()
{
  if (listen(socket_fd, 10) < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening on port " << sockaddr.sin_port << std::endl;

  // Now we need to accept the connection.

  unsigned long addrlen = sizeof(sockaddr);

  connection = accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (connection < 0)
  {
    std::cout << "Failed to grab connection." << std::endl;
    exit(EXIT_FAILURE);
  }

  // ************************

  char request[REQUEST_MAX_LENGTH];

  if (read(connection, request, sizeof(request)) < 0)
  {
    std::cout << "Failed reading the message." << std::endl;
    exit(EXIT_FAILURE);
  }

  handle_request(request);
}

void Sirocco::handle_request(char *request)
{
  // std::cout << "Request: " << request << std::endl;

  std::vector<std::string> tokens;

  Utils::tokenize(request, " ", tokens);

  // std::cout << "VERB: " << tokens[0] << std::endl;
  // std::cout << "PATH: " << tokens[1] << std::endl;

  http_url_t tk_request;

  HTTP::parse_url(tokens[1], &tk_request);

  // Utils::print_vector("T", tk_request.path);

  handlers[tokens[0] + "_" + tk_request.path[0]][tk_request.path.size() - 1](connection, tk_request);
}

void Sirocco::handle_response(std::string verb, std::string response_path, std::function<void(int, http_url_t)> callback)
{
  std::vector<std::string> tokens;
  Utils::tokenize(response_path, "/", tokens);

  /* Utils::print_vector("THR", tokens);

  std::cout << "HANDLER: " << verb + "_" + tokens[0] + "_" + std::to_string(tokens.size() - 1) << std::endl; */

  handlers[verb + "_" + tokens[0]][tokens.size() - 1] = callback;
}

void Sirocco::close_connections()
{
  close(connection);
  close(socket_fd);
  std::cout << "Closing socket" << std::endl;
}
