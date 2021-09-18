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
  response.set_content_type("text/plain");
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_json(std::string message)
{
  response.set_content_type("application/json");
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_html(std::string message)
{
  response.set_content_type("text/html");
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_not_implemented()
{
  response.set_status_code(501);
  response.set_content_type("text/html");
  std::string msg = response.compose_response("<h1>501 Not Implemented</h1>");
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_file(std::string file_path)
{
  std::string file = Utils::read_file(file_path);

  std::vector<std::string> file_tk;

  Utils::tokenize(file_path, "\n", file_tk);

  Utils::print_vector(file_tk);

  std::string extension = Utils::get_extension(file_path);

  std::cout << "File Extension: " << extension << std::endl;
  std::cout << "File Path: " << file_path << std::endl;

  response.set_status_code(200);
  response.set_content_type(http.get_content_type(extension));
  std::string msg = response.compose_response(file);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_server_error()
{
  response.set_status_code(500);
  response.set_content_type("text/html");
  std::string msg = response.compose_response("<h1>500 Server Error</h1>");
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
