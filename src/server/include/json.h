// json.h

#ifndef JSON_H // include guard
#define JSON_H

#include <map>
#include <string>
#include <iostream>

class JSON
{
private:
public:
  JSON();
  ~JSON();

  static std::string stringify(std::map<std::string, std::string>);
};

JSON::JSON()
{
}

JSON::~JSON()
{
}

std::string JSON::stringify(std ::map<std::string, std::string> json)
{
  std::string result = "{";

  for (auto it = json.rbegin(); it != json.rend(); ++it)
  {
    result += "\"" + it->first + "\":\"" + it->second + "\",";
  }

  result.pop_back();

  result += "}";

  return result;
}

#endif /* JSON_H */
