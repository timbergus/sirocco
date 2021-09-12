#include "response.h"

sirocco::Response::Response(int connection)
{
  this->connection = connection;
}

sirocco::Response::~Response()
{
}

std::string sirocco::Response::compose(std::string content)
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

void sirocco::Response::set_status(int status)
{
  sirocco::HTTP http;
  http_response.status_code = status;
  http_response.status_message = http.get_status_message(status);
}

void sirocco::Response::send_text(std::string message)
{
  http_response.content_type = "Content-Type: text/plain";
  std::string response = compose(message);
  send(connection, response.c_str(), response.size(), 0);
}

void sirocco::Response::send_json(std::string message)
{
  http_response.content_type = "Content-Type: application/json";
  std::string response = compose(message);
  send(connection, response.c_str(), response.size(), 0);
}

void sirocco::Response::send_html(std::string message)
{
  http_response.content_type = "Content-Type: text/html";
  std::string response = compose(message);
  send(connection, response.c_str(), response.size(), 0);
}
