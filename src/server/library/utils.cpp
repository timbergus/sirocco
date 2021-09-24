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

std::string Utils::stringify_vector(std::vector<std::string> tokens)
{
  std::string result = "[";

  for (auto token : tokens)
    result += "\"" + token + "\", ";

  result.pop_back();
  result.pop_back();

  result += "]";

  return result;
}

std::string Utils::stringify_map(std::map<std::string, std::string> tokens)
{
  std::string result = "{ ";

  for (auto token : tokens)
  {
    result += "\"" + token.first + "\": \"" + token.second + "\", ";
  }

  result.pop_back();
  result.pop_back();

  result += " }";

  return result;
}

std::string Utils::read_file(std::string file_name)
{
  std::ifstream file(file_name);

  if (file.is_open())
  {
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});

    std::string contents(buffer.begin(), buffer.end());

    file.close();

    return contents;
  }

  throw std::runtime_error("Could not open file: " + file_name);
}

void Utils::read_env_file(std::string file_name, std::map<std::string, std::string> &env)
{
  std::ifstream file(file_name.c_str());
  std::string line;
  while (std::getline(file, line))
  {
    std::vector<std::string> split_line;
    Utils::tokenize(line, "=", split_line);
    env[split_line[0]] = split_line[1];
  }
}
