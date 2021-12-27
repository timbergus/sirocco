// sirocco.h

#ifndef SIROCCO_H // include guard
#define SIROCCO_H

#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <functional>
#include <map>
#include <any>

#include "http.h"
#include "utils.h"
#include "comm.h"
#include "response.h"

class Sirocco
{
private:
  Comm comm;

  std::map<std::string, std::map<int, std::function<void(Comm)>>> handlers;

  std::string public_path;

  bool debug;

public:
  Sirocco(std::map<std::string, std::any>);
  ~Sirocco();

  void listening();

  void respond();

  void handle_response(std::string, std::string, std::function<void(Comm)>);

  void get(std::string, std::function<void(Comm)>);
  void post(std::string, std::function<void(Comm)>);
  void put(std::string, std::function<void(Comm)>);
  void patch(std::string, std::function<void(Comm)>);
  void del(std::string, std::function<void(Comm)>);

  void log(std::string);
};

Sirocco::Sirocco(std::map<std::string, std::any> options)
{
  if (auto public_path{options.find("public_path")}; public_path != std::end(options))
  {
    std::string pp = std::any_cast<const char *>(public_path->second);
    this->public_path = pp;
    comm.set_public_path(pp);
  }

  if (auto debug{options.find("debug")}; debug != std::end(options))
  {
    this->debug = std::any_cast<bool>(debug->second);
  }

  if (auto port{options.find("port")}; port != std::end(options))
  {
    comm.create_socket();
    comm.bind_socket(std::any_cast<int>(port->second));
  }
  else
  {
    throw std::runtime_error("No port specified");
  }
}

Sirocco::~Sirocco()
{
  comm.close_connection();
  comm.close_socket();
  std::cout << "Closing server." << std::endl;
}

void Sirocco::listening()
{
  comm.listen_connection();

  while (true)
  {
    comm.accept_connection();
    comm.read_request();
    respond();
  }
}

void Sirocco::respond()
{
  try
  {
    std::string base = "";

    if (comm.request.parsed.path.size() > 0)
    {
      base = comm.request.parsed.path[0];
    }

    handlers[comm.request.verb + "_" + base][comm.request.parsed.path.size() - 1](comm);
  }
  catch (const std::exception &e)
  {
    /**
     * If we have an error that means that we could be requesting a file.
     * If the public path has not been set, then we can't serve files, so
     * we'll just return a "not implemented".
     */

    if (public_path.empty())
    {
      comm.send_not_implemented();
    }
    else
    {
      if (comm.request.parsed.raw_path == "/")
      {
        // Files from the root path. We send the name.
        comm.send_file(comm.request.parsed.path[0]);
      }
      else
      {
        // Files from a sub-path. We send the full path.
        comm.send_file(comm.request.parsed.raw_path);
      }
    }
  }
}

void Sirocco::handle_response(std::string verb, std::string request_path, std::function<void(Comm)> callback)
{
  std::vector<std::string> tokens;
  Utils::tokenize(request_path, "/", tokens);

  std::string base = "";

  if (tokens.size() > 0)
  {
    base = tokens[0];
  }

  handlers[verb + "_" + base][tokens.size() - 1] = callback;
}

void Sirocco::get(std::string request_path, std::function<void(Comm)> callback)
{
  log("GET " + request_path);
  handle_response("GET", request_path, callback);
}

void Sirocco::post(std::string request_path, std::function<void(Comm)> callback)
{
  log("POST " + request_path);
  handle_response("POST", request_path, callback);
}

void Sirocco::put(std::string request_path, std::function<void(Comm)> callback)
{
  log("PUT " + request_path);
  handle_response("PUT", request_path, callback);
}

void Sirocco::patch(std::string request_path, std::function<void(Comm)> callback)
{
  log("PATCH " + request_path);
  handle_response("PATCH", request_path, callback);
}

void Sirocco::del(std::string request_path, std::function<void(Comm)> callback)
{
  log("DELETE " + request_path);
  handle_response("DELETE", request_path, callback);
}

void Sirocco::log(std::string message)
{
  if (debug)
  {
    std::cout << message << std::endl;
  }
}

#endif /* SIROCCO_H */
