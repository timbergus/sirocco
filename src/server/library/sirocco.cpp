#include "include/sirocco.h"

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

  // ************************

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

    if (comm.request.as_tokens.path.size() > 0)
      base = comm.request.as_tokens.path[0];

    handlers[comm.request.verb + "_" + base][comm.request.as_tokens.path.size() - 1](comm);
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
      comm.send_file(comm.request.as_tokens.path[0]);
    }
  }
}

void Sirocco::handle_response(std::string verb, std::string request_path, std::function<void(Comm)> callback)
{
  std::vector<std::string> tokens;
  Utils::tokenize(request_path, "/", tokens);

  std::string base = "";

  if (tokens.size() > 0)
    base = tokens[0];

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
