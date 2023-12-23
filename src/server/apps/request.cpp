// request.cpp

#include "request.h"
#include "utils.h"

void parse_request(std::string request, request_t &parsed_request)
{

  std::vector<std::string> request_tokens;

  split(request, " ", request_tokens);

  std::vector<std::string> path_query_tokens;
  std::vector<std::string> path_tokens;
  std::vector<std::string> query_tokens;

  if (request_tokens.size() > 0)
  {
    parsed_request.verb = request_tokens[0];
  }

  if (request_tokens.size() > 1)
  {
    split(request_tokens[1], "?", path_query_tokens);
    parsed_request.path = path_query_tokens[0];
    parsed_request.query = path_query_tokens[1];
  }

  if (path_query_tokens.size() > 0)
  {
    split(path_query_tokens[0], "/", path_tokens);
    parsed_request.path_tokens = path_tokens;
  }

  if (path_query_tokens.size() > 1)
  {
    split(path_query_tokens[1], "&", query_tokens);
  }

  std::map<std::string, std::string> query_tokens_map;

  for (auto q : query_tokens)
  {
    std::vector<std::string> q_tokens;
    split(q, "=", q_tokens);
    query_tokens_map[q_tokens[0]] = q_tokens[1];
  }

  parsed_request.query_tokens = query_tokens_map;
}
