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

  std::map<std::string, std::map<int, std::function<void(Comm, http_url_t)>>> handlers;

public:
  Sirocco(int);
  ~Sirocco();

  void listening();

  void handle_request(char *);

  void handle_response(std::string, std::string, std::function<void(Comm, http_url_t)>);

  void get(std::string, std::function<void(Comm, http_url_t)>);
  void post(std::string, std::function<void(Comm, http_url_t)>);
  void put(std::string, std::function<void(Comm, http_url_t)>);
  void del(std::string, std::function<void(Comm, http_url_t)>);
};

#endif /* SIROCCO_H */
