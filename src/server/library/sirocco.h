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

namespace sirocco
{

  class Sirocco
  {
  private:
    int REQUEST_MAX_LENGTH = 1024;

    std::map<std::string, std::function<void(int)>> handlers;

    int socket_fd;
    sockaddr_in sockaddr;
    int connection;
    std::vector<std::string> tokens;

    void close_connections();

  public:
    Sirocco(int);
    ~Sirocco();

    void listening();
    void parse_request(char *);
    void get(std::string, std::function<void(int)>);
    void post(std::string, std::function<void(int)>);
    void put(std::string, std::function<void(int)>);
    void del(std::string, std::function<void(int)>);
  };
} // namespace sirocco

#endif /* SIROCCO_H */
