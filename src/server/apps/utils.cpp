#include "utils.h"

void split(const std::string &sample, const std::string &delimeter, std::vector<std::string> &tokens)
{
  std::string::size_type beg = 0;

  for (auto end = 0; size_t(end = sample.find(delimeter, end)) != std::string::npos; ++end)
  {
    tokens.push_back(sample.substr(beg, end - beg));
    beg = end + 1;
  }

  tokens.push_back(sample.substr(beg));
}

std::string stringify_vector(const std::vector<std::string> &tokens)
{
  std::string result = "[";

  for (auto token : tokens)
    result += "\"" + token + "\", ";

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

std::string read_file(std::string file_name)
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

void read_env_file(std::string env_file, std::map<std::string, std::string> &env)
{
  std::ifstream file(env_file);
  std::string line;
  while (std::getline(file, line))
  {
    std::vector<std::string> split_line;
    split(line, "=", split_line);
    env[split_line[0]] = split_line[1];
  }
}
