#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "utils.h"

class Request
{

public:
  std::string verb;
  std::string path;
  std::string protocol;
  std::string query;
  std::vector<std::string> path_tokens;
  std::map<std::string, std::string> query_tokens;
  std::string payload;

public:
  Request();
  ~Request();

  void parse_request(std::string);
};
