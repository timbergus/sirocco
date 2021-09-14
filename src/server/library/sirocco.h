// sirocco.h

#ifndef SIROCCO_H // include guard
#define SIROCCO_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <functional>
#include <map>

#include "http.h"
#include "utils.h"

class Sirocco
{
private:
  int REQUEST_MAX_LENGTH{1024};

  std::map<std::string, std::map<int, std::function<void(int, http_url_t)>>> handlers;

  int socket_fd;
  sockaddr_in sockaddr;
  int connection;

  void close_connections();

public:
  Sirocco(int);
  ~Sirocco();

  void listening();

  void handle_request(char *);
  void handle_response(std::string, std::string, std::function<void(int, http_url_t)>);
};

#endif /* SIROCCO_H */
