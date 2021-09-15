// sirocco.h

#ifndef SIROCCO_H // include guard
#define SIROCCO_H

#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <functional>
#include <map>

#include "http.h"
#include "utils.h"
#include "comm.h"
#include "response.h"

class Sirocco
{
private:
  Comm comm;

  std::map<std::string, std::map<int, std::function<void(Comm)>>> handlers;

public:
  Sirocco(int);
  ~Sirocco();

  void listening();

  void respond();

  void handle_response(std::string, std::string, std::function<void(Comm)>);

  void get(std::string, std::function<void(Comm)>);
  void post(std::string, std::function<void(Comm)>);
  void put(std::string, std::function<void(Comm)>);
  void del(std::string, std::function<void(Comm)>);
};

#endif /* SIROCCO_H */
