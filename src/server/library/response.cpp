#include "include/response.h"

Response::Response()
{
}

Response::~Response()
{
}

std::string Response::compose(std::string content)
{
  char buffer[500];

  sprintf(buffer, "%s %d %s\n%s\n\n%s",
          http_response.protocol.c_str(),
          http_response.status_code,
          http_response.status_message.c_str(),
          http_response.content_type.c_str(),
          content.c_str());

  return buffer;
}

void Response::set_status(int status)
{
  HTTP http;
  http_response.status_code = status;
  http_response.status_message = http.get_status_message(status);
}

void Response::set_content_type(std::string content_type)
{
  http_response.content_type = content_type;
}
