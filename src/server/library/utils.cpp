#include "utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::vector<std::string> Utils::tokenize(std::string str, const char *delimeter)
{
  std::vector<std::string> tokens;

  const char *c_str = str.c_str();

  char *token = strtok((char *)c_str, delimeter);

  while (token)
  {
    tokens.push_back(token);
    token = strtok(NULL, delimeter);
  }

  return tokens;
}

std::vector<std::string> Utils::tokenize(char *str, const char *delimeter)
{
  std::vector<std::string> tokens;

  char *token = strtok(str, delimeter);

  while (token)
  {
    tokens.push_back(token);
    token = strtok(NULL, delimeter);
  }

  return tokens;
}
