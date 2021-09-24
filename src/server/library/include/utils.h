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

  static void tokenize(std::string, const char *, std::vector<std::string> &);
  static void tokenize(char *, const char *, std::vector<std::string> &);
  static std::string stringify_vector(std::vector<std::string>);
  static std::string stringify_map(std::map<std::string, std::string>);

  // Static files
  static std::string read_file(std::string);
  static void read_env_file(std::string, std::map<std::string, std::string> &);
};

#endif /* UTILS_H */
