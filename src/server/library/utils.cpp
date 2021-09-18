#include "include/utils.h"

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

std::string Utils::read_file(std::string file_name)
{
  std::string contents;
  std::ifstream file(file_name);

  std::string line;

  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      contents += "\n";
      contents += line;
    }
    file.close();

    return contents;
  }

  throw std::runtime_error("Could not open file: " + file_name);
}

std::string Utils::get_extension(std::string file_name)
{
  std::size_t found = file_name.find_last_of(".");
  if (found != std::string::npos)
  {
    return file_name.substr(found + 1);
  }

  throw std::runtime_error("Could not get extension from file name.");
}
