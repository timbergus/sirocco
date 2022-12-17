// utils.h

#ifndef UTILS_H // include guard
#define UTILS_H

#include <iostream>
#include <map>
#include <vector>
#include <string.h>
#include <fstream>

class Utils
{
private:
  /* data */
public:
  Utils(/* args */);
  ~Utils();

  static void split(std::string, std::string, std::vector<std::string> &);
  static std::string stringify_vector(std::vector<std::string>);
  static std::string stringify_map(std::map<std::string, std::string>);

  // Static files
  static std::string read_file(std::string);
  static void read_env_file(std::string, std::map<std::string, std::string> &);
};

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::split(std::string sample, std::string delimeter, std::vector<std::string> &tokens)
{
  std::string::size_type beg = 0;

  for (auto end = 0; size_t(end = sample.find(delimeter, end)) != std::string::npos; ++end)
  {
    tokens.push_back(sample.substr(beg, end - beg));
    beg = end + 1;
  }

  tokens.push_back(sample.substr(beg));
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
    Utils::split(line, "=", split_line);
    env[split_line[0]] = split_line[1];
  }
}

#endif /* UTILS_H */
