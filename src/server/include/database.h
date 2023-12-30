#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <fmt/core.h>
#include <map>

#include "utils.h"

class Database
{
private:
  sqlite3 *db = nullptr;
  std::map<std::string, std::string> env;

public:
  Database();
  ~Database();

  void execute_query(std::string, int (*)(void *, int, char **, char **));
};
