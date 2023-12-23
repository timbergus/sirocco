#include "utils.h"

void split(std::string_view sample, std::string_view delimeter, std::vector<std::string> &tokens)
{
  std::string::size_type beg = 0;

  for (auto end = 0; (end = sample.find(delimeter, end)) != static_cast<int>(std::string::npos); ++end)
  {
    tokens.push_back(static_cast<std::string>(sample.substr(beg, end - beg)));
    beg = end + 1;
  }

  tokens.push_back(static_cast<std::string>(sample.substr(beg)));
}

std::string stringify_vector(const std::vector<std::string> &tokens)
{
  std::string result = "[";

  for (auto token : tokens)
  {
    result += "\"" + token + "\", ";
  }

  result.pop_back();
  result.pop_back();

  result += "]";

  return result;
}

std::string stringify_map(const std::map<std::string, std::string> &tokens)
{
  std::string result = "{\n";

  for (auto token : tokens)
  {
    result += "  \"" + token.first + "\": \"" + token.second + "\",\n";
  }

  result.pop_back();
  result.pop_back();

  result += "\n}";

  return result;
}

std::string read_file(std::string_view file_name)
{
  std::ifstream file{file_name};

  if (file.is_open())
  {
    std::stringstream contents;

    contents << file.rdbuf();

    return contents.str();
  }
  else
  {
    std::cerr << "Could not open file " << file_name << " :" << strerror(errno) << std::endl;
    return static_cast<std::string>("");
  }
}

void read_env_file(std::string_view env_file, std::map<std::string, std::string> &env)
{
  std::ifstream file{env_file};

  std::string line;

  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      std::vector<std::string> split_line;

      split(line, "=", split_line);

      env[split_line[0]] = split_line[1];
    }
  }
  else
  {
    std::cerr << "Could not open env file: " << strerror(errno) << std::endl;
  }
}
