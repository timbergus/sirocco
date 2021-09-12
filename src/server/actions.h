#include <functional>

#include "library/json.h"
#include "library/response.h"

std::function<void(int)> get_home = [](int connection)
{
  sirocco::Response response(connection);
  response.set_status(500);
  response.send_html("<h1>Server is dead!</h1>");
};

std::function<void(int)> post_home = [](int connection)
{
  sirocco::Response response(connection);
  response.set_status(200);
  response.send_text("Thanks for the info!");
};

std::function<void(int)> put_home = [](int connection)
{
  sirocco::Response response(connection);
  response.set_status(202);
  std::map<std::string, std::string> data{{"hello", "world"}, {"bye", "moon"}};
  response.send_json(sirocco::JSON::stringify(data));
};

std::function<void(int)> delete_home = [](int connection)
{
  sirocco::Response response(connection);
  response.set_status(401);
  response.send_html("<h1>Sorry. Not enough permission!</h1>");
};
