#include "request.h"

Request::Request()
{
}

Request::~Request()
{
}

void Request::parse_request()
{
  std::vector<std::string> as_string_tk;

  Utils::tokenize(as_string, " ", as_string_tk);

  std::vector<std::string> path_query_tk;
  std::vector<std::string> path_tk;
  std::vector<std::string> query_tk;

  Utils::tokenize(as_string_tk[1], "?", path_query_tk);
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

  verb = as_string_tk[0];

  as_tokens.path = path_tk;
  as_tokens.query = query_map;
}
