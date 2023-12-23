#include "response.h"

Response::Response(/* args */)
{
}

Response::~Response()
{
}

void Response::set_status_code(int status_code)
{
  this->status_code = status_code;
  this->status_message = status_messages[status_code];
}

void Response::set_content_type(std::string_view content_type)
{
  this->content_type = content_types[static_cast<std::string>(content_type)];
}

std::string Response::compose_response(std::string content)
{
  this->content_length = content.size();
  this->connection_status = "close";

  std::string message{};

  message += fmt::format("{} {} {}\n", this->protocol, this->status_code, this->status_message);
  message += fmt::format("Content-Type: {}\n", this->content_type);
  message += fmt::format("Content-Length: {}\n", this->content_length);
  message += fmt::format("Connection: {}\n", this->connection_status);
  message += "\n";
  message += content;

  return message;
}
