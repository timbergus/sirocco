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

class Comm
{
private:
public:
  int port;
  int socket_fd;
  int connection;
  sockaddr_in sockaddr;

  char request[1024];

  Comm(/* args */);
  ~Comm();

  void create_socket();
  void bind_socket(int);
  void listen_connection();
  void accept_connection();
  void read_request();
  void close_connection();
  void close_socket();
};

#endif /* COMM_H */
