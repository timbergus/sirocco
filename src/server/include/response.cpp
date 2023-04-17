// response.cpp

#include <fmt/core.h>

#include "response.h"
#include "http.h"

void set_status_code(int status_code, response_t &response)
{
  response.status_code = status_code;
  response.status_message = status_messages[status_code];
}

void set_content_type(std::string content_type, response_t &response)
{
  response.content_type = content_types[content_type];
}

std::string compose_response(std::string content, response_t &response)
{
  response.content_length = content.size();
  response.connection_status = "close";

  std::string message;

  message += fmt::format("{} {} {}\n", response.protocol, response.status_code, response.status_message);
  message += fmt::format("Content-Type: {}\n", response.content_type);
  message += fmt::format("Content-Length: {}\n", response.content_length);
  message += fmt::format("Connection: {}\n", response.connection_status);
  message += "\n";
  message += content;

  return message;
}
