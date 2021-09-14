// utils.h

#ifndef UTILS_H // include guard
#define UTILS_H

#include <vector>
#include <string>

class Utils
{
private:
  /* data */
public:
  Utils(/* args */);
  ~Utils();

  static std::vector<std::string> tokenize(std::string, const char *);
  static std::vector<std::string> tokenize(char *, const char *);
};

#endif /* UTILS_H */
