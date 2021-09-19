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

#endif /* REQUEST_H */
