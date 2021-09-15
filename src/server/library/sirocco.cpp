#include "sirocco.h"

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
  comm.accept_connection();

  // ************************

  comm.read_request();

  handle_request(comm.request);
}

void Sirocco::handle_request(char *request)
{
  // std::cout << "Request: " << request << std::endl;

  std::vector<std::string> tokens;

  Utils::tokenize(request, " ", tokens);

  // std::cout << "VERB: " << tokens[0] << std::endl;
  // std::cout << "PATH: " << tokens[1] << std::endl;

  http_url_t tk_request;

  HTTP::parse_url(tokens[1], &tk_request);

  // Utils::print_vector("T", tk_request.path);

  handlers[tokens[0] + "_" + tk_request.path[0]][tk_request.path.size() - 1](comm.connection, tk_request);
}

void Sirocco::handle_response(std::string verb, std::string response_path, std::function<void(int, http_url_t)> callback)
{
  std::vector<std::string> tokens;
  Utils::tokenize(response_path, "/", tokens);

  /* Utils::print_vector("THR", tokens);

  std::cout << "HANDLER: " << verb + "_" + tokens[0] + "_" + std::to_string(tokens.size() - 1) << std::endl; */

  handlers[verb + "_" + tokens[0]][tokens.size() - 1] = callback;
}

void Sirocco::get(std::string response_path, std::function<void(int, http_url_t)> callback)
{
  handle_response("GET", response_path, callback);
}

void Sirocco::post(std::string response_path, std::function<void(int, http_url_t)> callback)
{
  handle_response("POST", response_path, callback);
}

void Sirocco::put(std::string response_path, std::function<void(int, http_url_t)> callback)
{
  handle_response("PUT", response_path, callback);
}

void Sirocco::del(std::string response_path, std::function<void(int, http_url_t)> callback)
{
  handle_response("DELETE", response_path, callback);
}
