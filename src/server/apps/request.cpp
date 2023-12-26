#include "request.h"

Request::Request()
{
}

Request::~Request()
{
}

void Request::parse_request(std::string request)
{
  std::vector<std::string> request_tokens;

  split(request, "\r", request_tokens);

  // Remove the additional \n at the beginning of each line.
  // It appears because every new line has \r\n, so because
  // we have splitted by \r, the \n character remains.

  for (int i = 1; i < static_cast<int>(request_tokens.size()); i++)
  {
    request_tokens[i].erase(request_tokens[i].begin());
  }

  // And also the empty lines.

  std::erase_if(request_tokens, [](auto &&str)
                { return str.length() == 0; });

  // Extract the path and the query params.

  std::vector<std::string> path_query_tokens;
  std::vector<std::string> path_tokens;
  std::vector<std::string> query_tokens;
  std::vector<std::string> path_path_tokens;
  std::map<std::string, std::string> query_tokens_map;

  split(request_tokens[0], " ", path_tokens);

  this->verb = path_tokens[0];
  this->protocol = path_tokens[2];

  split(path_tokens[1], "?", path_query_tokens);

  this->path = path_query_tokens[0];
  this->query = path_query_tokens[1];

  split(path_query_tokens[0], "/", path_path_tokens);

  std::erase_if(path_path_tokens, [](auto &&str)
                { return str.length() == 0; });

  this->path_tokens = path_path_tokens;

  if (path_query_tokens[1].length() > 0)
  {
    split(path_query_tokens[1], "&", query_tokens);

    for (auto q : query_tokens)
    {
      std::vector<std::string> q_tokens;
      split(q, "=", q_tokens);
      query_tokens_map[q_tokens[0]] = q_tokens[1];
    }

    this->query_tokens = query_tokens_map;
  }

  // Check if we have payload (must exist content type).

  int count = std::count(request_tokens.begin(), request_tokens.end(), "Content-Type: application/json") +
              std::count(request_tokens.begin(), request_tokens.end(), "content-type: application/json");

  if (count > 0)
  {
    this->payload = request_tokens[request_tokens.size() - 1];
  }
}
