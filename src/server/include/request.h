#pragma once

#include <string>
#include <vector>
#include <map>

#include "utils.h"

class Request
{

public:
  std::string verb;
  std::string path;
  std::string query;
  std::vector<std::string> path_tokens;
  std::map<std::string, std::string> query_tokens;

public:
  Request();
  ~Request();

  void parse_request(std::string);
};
