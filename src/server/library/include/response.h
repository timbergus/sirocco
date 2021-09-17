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
  struct http_response_t
  {
    std::string protocol = "HTTP/1.1";
    int status_code;
    std::string status_message;
    std::string content_type;
    int content_length;
    std::string connection_status;
  } http_response;

public:
  Response();
  ~Response();

  void set_status_code(int);
  void set_content_type(std::string);

  std::string compose_response(std::string);
};

#endif /* RESPONSE_H */
