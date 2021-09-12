#include "json.h"

sirocco::JSON::JSON()
{
}

sirocco::JSON::~JSON()
{
}

std::string sirocco::JSON::stringify(std ::map<std::string, std::string> json)
{
  std::string result = "{";

  for (auto it = json.rbegin(); it != json.rend(); ++it)
  {
    result += "\"" + it->first + "\":\"" + it->second + "\",";
  }

  result += "}";

  return result;
}
