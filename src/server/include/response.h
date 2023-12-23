#pragma once

#include <string>
#include <string_view>
#include <fmt/core.h>

#include "http.h"

class Response
{
private:
  std::string protocol = "HTTP/1.1";
  int status_code;
  std::string status_message;
  std::string content_type;
  int content_length;
  std::string connection_status;

public:
  Response();
  ~Response();

  void set_status_code(int);
  void set_content_type(std::string_view);

  std::string compose_response(std::string);
};
