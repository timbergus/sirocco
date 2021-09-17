// utils.h

#ifndef UTILS_H // include guard
#define UTILS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
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
  static void print_vector(std::string, std::vector<std::string>);
  static std::string print_vector(std::vector<std::string>);
  static void print_map(std::string, std::map<std::string, std::string>);
  static std::string print_map(std::map<std::string, std::string>);

  // Static files
  static void read_file(std::string, std::string &);
};

#endif /* UTILS_H */
