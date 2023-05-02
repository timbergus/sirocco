#pragma once

#include <string>

struct response_t
{
  std::string protocol = "HTTP/1.1";
  int status_code;
  std::string status_message;
  std::string content_type;
  int content_length;
  std::string connection_status;
};

void set_status_code(int, response_t &);
void set_content_type(std::string, response_t &);

std::string compose_response(std::string, response_t &);
