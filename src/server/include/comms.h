#pragma once

#include <filesystem>
#include <fmt/color.h>
#include <fmt/core.h>
#include <map>
#include <string>

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include "request.h"
#include "response.h"

class Comms {
private:
  std::map<std::string, std::string> env;

#ifdef _WIN32
  SOCKET socket_fd;
#else
  int socket_fd;
#endif

  int connection;
  sockaddr_in sockaddr;

public:
  int port;
  Request request;
  Response response;
  std::filesystem::path public_path;

  Comms();
  ~Comms();

  void set_public_path(std::string);

  void create_socket();
  void bind_socket(int);
  void listen_connection();
  void accept_connection();
  void read_request();

  void close_connection();
  void close_socket();

  void send_contents(std::string, std::string, int = 200);
  void send_file(std::string);

  void send_not_implemented();
  void send_server_error();
};
