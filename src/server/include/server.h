#pragma once

#include <string>
#include <map>
#include <any>

#include "comms.h"

class Server
{
private:
  Comms comms;

  std::map<std::string, std::function<void(Comms)>> handlers;

  std::string public_path;

  bool debug;

public:
  Server(std::map<std::string, std::any>);
  ~Server();

  void listening();

  void respond();

  void handle_response(std::string, std::string, std::function<void(Comms)>);

  void get(std::string, std::function<void(Comms)>);
  void post(std::string, std::function<void(Comms)>);
  void put(std::string, std::function<void(Comms)>);
  void patch(std::string, std::function<void(Comms)>);
  void del(std::string, std::function<void(Comms)>);

  void log(std::string);
};
