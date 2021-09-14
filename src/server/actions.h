#include <functional>

#include "library/json.h"
#include "library/response.h"

std::function<void(int, http_url_t)> get_home = [](int connection, http_url_t request)
{
  Response response(connection);
  response.set_status(500);
  response.send_html("<h1>Server is dead!</h1><br /><p>" + Utils::print_vector(request.path) + "</p><br /><p>" + Utils::print_map(request.query) + "</p>");
};

std::function<void(int, http_url_t)> post_home = [](int connection, __attribute__((unused)) http_url_t request)
{
  Response response(connection);
  response.set_status(200);
  response.send_text("Thanks for the info!");
};

std::function<void(int, http_url_t)> put_home = [](int connection, __attribute__((unused)) http_url_t request)
{
  Response response(connection);
  response.set_status(202);
  std::map<std::string, std::string> data{{"hello", "world"}, {"bye", "moon"}};
  response.send_json(JSON::stringify(data));
};

std::function<void(int, http_url_t)> delete_home = [](int connection, __attribute__((unused)) http_url_t request)
{
  Response response(connection);
  response.set_status(401);
  response.send_html("<h1>Sorry. Not enough permission!</h1>");
};
