// comm.h

#ifndef COMM_H // include guard
#define COMM_H

#include <iostream>
// create socket
#include <sys/socket.h>
// bind socket
#include <netinet/in.h>
// read request
#include <unistd.h>
// file paths
#include <filesystem>

#include "request.h"
#include "response.h"
#include "http.h"
#include "utils.h"

class Comm
{
private:
  HTTP http;
  std::filesystem::path public_path;
  std::map<std::string, std::string> env;

public:
  int port;
  int socket_fd;
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

#endif /* COMM_H */
