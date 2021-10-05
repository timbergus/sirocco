// request.h

#ifndef REQUEST_H // include guard
#define REQUEST_H

#include <map>
#include <vector>

#include "utils.h"

class Request
{
private:
  /* data */
public:
  char as_string[1024];

  std::string verb;

  struct request_t
  {
    std::string raw_path;
    std::vector<std::string> path;
    std::map<std::string, std::string> query;
  } parsed;

  Request();
  ~Request();

  void parse_request();
};

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

  parsed.raw_path = as_string_tk[1];
  parsed.path = path_tk;
  parsed.query = query_map;
}

#endif /* REQUEST_H */
