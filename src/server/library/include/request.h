// request.h

#ifndef REQUEST_H // include guard
#define REQUEST_H

#include <map>
#include <vector>

#include "utils.h"

class Request
{
private:
public:
  char as_string[1024];

  std::string verb;

  struct request_t
  {
    std::vector<std::string> path;
    std::map<std::string, std::string> query;
  } as_tokens;

  Request();
  ~Request();

  void parse_request();
};

#endif /* REQUEST_H */
