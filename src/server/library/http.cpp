#include "http.h"

HTTP::HTTP()
{
}

HTTP::~HTTP()
{
}

std::string HTTP::get_status_message(int http_status_code)
{
  return http_status_messages[http_status_code];
}

void HTTP::parse_url(std::string url, http_url *http_url)
{
  std::vector<std::string> blocks = Utils::tokenize(url, "?");

  for (auto block : blocks)
    std::cout << "B: " << block << std::endl;

  http_url->params = Utils::tokenize(blocks[0], "/");

  for (auto param : http_url->params)
    std::cout << "P: " << param << std::endl;

  http_url->query = Utils::tokenize(blocks[1], "&");

  for (auto query : http_url->query)
    std::cout << "Q: " << query << std::endl;

  http_url->path = http_url->params[0];
}
