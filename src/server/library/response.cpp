#include "response.h"

Response::Response()
{
}

Response::~Response()
{
}

std::string Response::compose_response(std::string content)
{
  http_response.content_length = content.size();
  http_response.connection_status = "close";

  std::string message = http_response.protocol + " " +
                        std::to_string(http_response.status_code) + " " +
                        http_response.status_message + "\n" +
                        "Content-Type: " + http_response.content_type + "\n" +
                        "Content-Length: " + std::to_string(http_response.content_length) + "\n" +
                        "Connection: " + http_response.connection_status + "\n\n" +
                        content;

  return message;
}

void Response::set_status_code(int status)
{
  http_response.status_code = status;
  http_response.status_message = http.get_status_message(status);
}

void Response::set_content_type(std::string content_type)
{
  http_response.content_type = content_type;
}
