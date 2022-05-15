// comm.h

#ifndef COMM_H // include guard
#define COMM_H

#include <iostream>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
// create socket
#include <sys/socket.h>
// bind socket
#include <netinet/in.h>
// read request
#include <unistd.h>
#endif

// file paths
#include <filesystem>

#include "request.h"
#include "response.h"
#include "http.h"
#include "utils.h"
#include "color.h"

class Comm
{
private:
  Color palette;
  HTTP http;
  std::filesystem::path public_path;
  std::map<std::string, std::string> env;

public:
  int port;
#ifdef _WIN32
  SOCKET socket_fd;
#else
  int socket_fd;
#endif
  int connection;
  sockaddr_in sockaddr;

  // Constructor.

  Request request;
  Response response;

  Comm(/* args */);
  ~Comm();

  void set_public_path(std::string);

  void create_socket();
  void bind_socket(int);
  void listen_connection();
  void accept_connection();
  void read_request();

  // Response
  void send_text(std::string);
  void send_json(std::string);
  void send_html(std::string);
  void send_file(std::string);

  void send_not_implemented();
  void send_server_error();

  void close_connection();
  void close_socket();
};

Comm::Comm()
{
  Utils::read_env_file("src/server/.env", env);
}

Comm::~Comm()
{
}

void Comm::set_public_path(std::string public_path)
{
  std::filesystem::path p(public_path);
  this->public_path = p.lexically_normal();
}

void Comm::create_socket()
{
#ifdef _WIN32
  WSADATA wsaData;
  WORD DllVersion = MAKEWORD(2, 2);

  if (WSAStartup(DllVersion, &wsaData) != 0)
  {
    std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
    exit(EXIT_FAILURE);
  }
#endif

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#ifdef _WIN32
  if (socket_fd == INVALID_SOCKET)
  {
    std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
    WSACleanup();
    exit(EXIT_FAILURE);
  }
#else
  if (socket_fd == -1)
  {
    std::cerr << "Error at socket(): " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
#endif
}

void Comm::bind_socket(int port)
{
  this->port = port;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << fmt::format("Failed to bind to port {}. Errno: {}\n", port, errno);
    exit(EXIT_FAILURE);
  }
}

void Comm::listen_connection()
{
  if (listen(socket_fd, 10) < 0)
  {
    std::cout << fmt::format("Failed to listen on socket. Errno: {}\n", errno);
    exit(EXIT_FAILURE);
  }

  const std::string formattedMessage = palette.set_color("Listening on:", "green");
  const std::string formattedPortName = palette.set_color(std::to_string(port), "yellow");
  std::cout << fmt::format("\n{} http://localhost:{}\n", formattedMessage, formattedPortName);
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
#ifdef _WIN32
  int n = recv(connection, request.as_string, sizeof(request.as_string), 0);
#else
  int n = read(connection, request.as_string, sizeof(request.as_string));
#endif
  if (n < 0)
  {
    std::cout << "Failed reading the message." << std::endl;
    exit(EXIT_FAILURE);
  }

  request.parse_request();
}

void Comm::send_text(std::string message)
{
  response.set_content_type(http.get_content_type("txt"));
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_json(std::string message)
{
  response.set_content_type(http.get_content_type("json"));
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_html(std::string message)
{
  response.set_content_type(http.get_content_type("html"));
  std::string msg = response.compose_response(message);
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_not_implemented()
{
  response.set_status_code(501);
  response.set_content_type(http.get_content_type("html"));
  std::string msg = response.compose_response("<h1>501 Not Implemented</h1>");
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::send_file(std::string file_name)
{
  std::string path = fmt::format("{}/{}/{}", env["ROOT_PATH"], public_path.string(), file_name);
  std::filesystem::path file_path(path);

  std::string file = Utils::read_file(file_path.lexically_normal().string());

  response.set_status_code(200);
  response.set_content_type(http.get_content_type(file_path.extension().string()));
  std::string message = response.compose_response(file);
  send(connection, message.c_str(), message.size(), 0);
}

void Comm::send_server_error()
{
  response.set_status_code(500);
  response.set_content_type(http.get_content_type("html"));
  std::string msg = response.compose_response("<h1>500 Server Error</h1>");
  send(connection, msg.c_str(), msg.size(), 0);
}

void Comm::close_connection()
{
#ifdef _WIN32
  closesocket(connection);
#else
  close(connection);
#endif
}

void Comm::close_socket()
{
#ifdef _WIN32
  closesocket(socket_fd);
  WSACleanup();
#else
  close(socket_fd);
#endif
}

#endif /* COMM_H */
