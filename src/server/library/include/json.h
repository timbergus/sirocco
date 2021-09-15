// json.h

#ifndef JSON_H // include guard
#define JSON_H

#include <map>
#include <string>
#include <iostream>

class JSON
{
private:
public:
  JSON();
  ~JSON();

  static std::string stringify(std::map<std::string, std::string>);
};

#endif /* JSON_H */