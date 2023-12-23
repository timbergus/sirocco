// server.cpp

#include <iostream>

#include "server.h"
#include "utils.h"

Server::Server(std::map<std::string, std::any> options)
{
  if (auto public_path{options.find("public_path")}; public_path != std::end(options))
  {
    std::string path = std::any_cast<const char *>(public_path->second);
    comms.set_public_path(path);
  }

  if (auto debug{options.find("debug")}; debug != std::end(options))
  {
    this->debug = std::any_cast<bool>(debug->second);
  }

  if (auto port{options.find("port")}; port != std::end(options))
  {
    comms.create_socket();
    comms.bind_socket(std::any_cast<int>(port->second));
  }
  else
  {
    throw std::runtime_error("No port specified");
  }
}

Server::~Server()
{
  comms.close_connection();
  comms.close_socket();
  std::cout << "Closing server." << std::endl;
}

void Server::listening()
{
  comms.listen_connection();

  while (true)
  {
    comms.accept_connection();
    comms.read_request();
    respond();
  }
}

void Server::respond()
{
  try
  {
    std::string base = "";

    if (comms.request.path.size() > 0)
    {
      base = comms.request.path[0];
    }

    handlers[comms.request.verb + "_" + comms.request.path](comms);
  }
  catch (const std::exception &e)
  {
    /**
     * If we have an error that means that we could be requesting a file.
     * If the public path has not been set, then we can't serve files, so
     * we'll just return a "not implemented".
     */

    if (comms.public_path.empty())
    {
      comms.send_not_implemented();
    }
    else
    {
      if (comms.request.path == "/")
      {
        // Files from the root path. We send the name.
        comms.send_file(comms.request.path_tokens[1]);
      }
      else
      {
        // Files from a sub-path. We send the full path.
        comms.send_file(comms.request.path);
      }
    }
  }
}

void Server::handle_response(std::string verb, std::string request_path, std::function<void(Comms)> callback)
{
  handlers[verb + "_" + request_path] = callback;
}

void Server::get(std::string request_path, std::function<void(Comms)> callback)
{
  log("GET " + request_path);
  handle_response("GET", request_path, callback);
}

void Server::post(std::string request_path, std::function<void(Comms)> callback)
{
  log("POST " + request_path);
  handle_response("POST", request_path, callback);
}

void Server::put(std::string request_path, std::function<void(Comms)> callback)
{
  log("PUT " + request_path);
  handle_response("PUT", request_path, callback);
}

void Server::patch(std::string request_path, std::function<void(Comms)> callback)
{
  log("PATCH " + request_path);
  handle_response("PATCH", request_path, callback);
}

void Server::del(std::string request_path, std::function<void(Comms)> callback)
{
  log("DELETE " + request_path);
  handle_response("DELETE", request_path, callback);
}

void Server::log(std::string message)
{
  if (debug)
  {
    std::cout << message << std::endl;
  }
}
