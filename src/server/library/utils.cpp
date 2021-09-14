#include "utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::tokenize(std::string str, const char *delimeter, std::vector<std::string> &tokens)
{
  char *token = strtok((char *)str.c_str(), delimeter);

  while (token)
  {
    tokens.push_back(token);
    token = strtok(NULL, delimeter);
  }
}

void Utils::tokenize(char *str, const char *delimeter, std::vector<std::string> &tokens)
{
  char *token = strtok(str, delimeter);

  while (token)
  {
    tokens.push_back(token);
    token = strtok(NULL, delimeter);
  }
}

void Utils::print_vector(std::string name, std::vector<std::string> tokens)
{
  std::cout << "* " + name + ":" << std::endl;
  for (auto token : tokens)
    std::cout << token << std::endl;
}

std::string Utils::print_vector(std::vector<std::string> tokens)
{
  std::string result = "[";

  for (auto token : tokens)
    result += "\"" + token + "\", ";

  result.pop_back();
  result.pop_back();

  result += "]";

  return result;
}

void Utils::print_map(std::string name, std::map<std::string, std::string> tokens)
{
  std::cout << "* " + name + ":" << std::endl;
  for (auto token : tokens)
    std::cout << "{\"" << token.first << "\": \"" << token.second << "\"}" << std::endl;
}

std::string Utils::print_map(std::map<std::string, std::string> tokens)
{
  std::string result = "{ ";

  for (auto token : tokens)
    result += "\"" + token.first + "\": \"" + token.second + "\", ";

  result.pop_back();
  result.pop_back();

  result += " }";

  return result;
}
