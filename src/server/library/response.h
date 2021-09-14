// response.h

#ifndef RESPONSE_H // include guard
#define RESPONSE_H

#include <string>
#include <stdio.h>
#include <netinet/in.h>
#include <map>

#include "http.h"

class Response
{
private:
  int connection;
  struct http_response_struct
  {
    std::string protocol = "HTTP/1.1";
    int status_code;
    std::string status_message;
    std::string content_type;
  } http_response;

  std::string compose(std::string);

public:
  Response(int);
  ~Response();

  void set_status(int);
  void send_text(std::string);
  void send_json(std::string);
  void send_html(std::string);
};

#endif /* RESPONSE_H */
