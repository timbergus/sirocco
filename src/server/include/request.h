#pragma once

#include <string>
#include <vector>
#include <map>

struct request_t
{
  std::string verb;
  std::string path;
  std::string query;
  std::vector<std::string> path_tokens;
  std::map<std::string, std::string> query_tokens;
};

void parse_request(std::string, request_t &);
