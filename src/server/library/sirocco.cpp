#include "include/sirocco.h"

Sirocco::Sirocco(int port)
{
  comm.create_socket();
  comm.bind_socket(port);
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
    // If we have an error that means that we could bb requested a file.
    // So we check if the request has the extension, and we send the file.

    // TODO #4 Clean this part.

    if (public_path.empty())
    {
      comm.send_not_implemented();
    }
    else
    {
      comm.send_file(public_path + "/" + comm.request.as_tokens.path[0]);
    }
  }
}

void Sirocco::set_public_path(std::string path)
{
  public_path = "src/server/" + path;
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
  handle_response("GET", request_path, callback);
}

void Sirocco::post(std::string request_path, std::function<void(Comm)> callback)
{
  handle_response("POST", request_path, callback);
}

void Sirocco::put(std::string request_path, std::function<void(Comm)> callback)
{
  handle_response("PUT", request_path, callback);
}

void Sirocco::patch(std::string request_path, std::function<void(Comm)> callback)
{
  handle_response("PATCH", request_path, callback);
}

void Sirocco::del(std::string request_path, std::function<void(Comm)> callback)
{
  handle_response("DELETE", request_path, callback);
}
