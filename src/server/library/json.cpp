#include "json.h"

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

  result += "}";

  return result;
}
