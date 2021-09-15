#include "include/comm.h"

Comm::Comm()
{
}

Comm::~Comm()
{
}

void Comm::create_socket()
{
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    std::cout << "Error creating socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Comm::bind_socket(int port)
{
  this->port = port;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Comm::listen_connection()
{
  if (listen(socket_fd, 10) < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Listening on port " << port << std::endl;
}

void Comm::accept_connection()
{
  unsigned long addrlen = sizeof(sockaddr);

  connection = accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  if (connection < 0)
  {
    std::cout << "Failed to grab connection." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Comm::read_request()
{
  if (read(connection, request.as_string, sizeof(request.as_string)) < 0)
  {
    std::cout << "Failed reading the message." << std::endl;
    exit(EXIT_FAILURE);
  }

  request.parse_request();
}

void Comm::send_text(std::string message)
{
  response.set_content_type("Content-Type: text/plain");
  std::string msg = response.compose(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_json(std::string message)
{
  response.set_content_type("Content-Type: application/json");
  std::string msg = response.compose(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_html(std::string message)
{
  response.set_content_type("Content-Type: text/html");
  std::string msg = response.compose(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::close_connection()
{
  close(connection);
}

void Comm::close_socket()
{
  close(socket_fd);
}
