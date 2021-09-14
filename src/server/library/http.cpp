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

void HTTP::parse_url(std::string url, http_url_t *http_url)
{
  // std::cout << "URL: " << url << std::endl;

  std::vector<std::string> path_query_tk;
  std::vector<std::string> path_tk;
  std::vector<std::string> query_tk;

  Utils::tokenize(url, "?", path_query_tk);
  Utils::tokenize(path_query_tk[0], "/", path_tk);
  Utils::tokenize(path_query_tk[1], "&", query_tk);

  std::map<std::string, std::string> path_map;
  std::map<std::string, std::string> query_map;

  for (auto q : query_tk)
  {
    std::vector<std::string> q_tk;
    Utils::tokenize(q, "=", q_tk);
    query_map[q_tk[0]] = q_tk[1];
  }

  http_url->path = path_tk;
  http_url->query = query_map;

  // Utils::print_vector("Path", path_tk);
  // Utils::print_map("Query", query_map);
}
