#include "include/response.h"

Response::Response()
{
}

Response::~Response()
{
}

std::string Response::compose_response(std::string content)
{
  char buffer[1024];

  http_response.content_length = content.size();
  http_response.connection_status = "close";

  sprintf(buffer, "%s %d %s\nContent-Type: %s\nContent-Length: %d\nConnection: %s\n\n%s",
          http_response.protocol.c_str(),
          http_response.status_code,
          http_response.status_message.c_str(),
          http_response.content_type.c_str(),
          http_response.content_length,
          http_response.connection_status.c_str(),
          content.c_str());

  return buffer;
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
